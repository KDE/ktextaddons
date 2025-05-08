/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidget.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogenerateengineutil.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessage.h"
#include "core/textautogeneratemessagesmodel.h"
#include "core/textautogeneratetextclient.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/textautogenerateheaderwidget.h"
#include "widgets/textautogeneratehistorywidget.h"
#include "widgets/textautogenerateresultwidget.h"
#include "widgets/textautogeneratetextlineeditwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KSplitterCollapserButton>
#include <QKeyEvent>
#include <QSplitter>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutogenerateWidget::TextAutogenerateWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateResultWidget(new TextAutogenerateResultWidget(this))
    , mTextAutoGenerateTextLineEditWidget(new TextAutoGenerateTextLineEditWidget(this))
    , mSplitter(new QSplitter(this))
    , mHistoryWidget(new TextAutogenerateHistoryWidget(this))
    , mHeaderWidget(new TextAutogenerateHeaderWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
    mHeaderWidget->setObjectName(QStringLiteral("mHeaderWidget"));
    mainLayout->addWidget(mHeaderWidget);

    mSplitter->setOrientation(Qt::Horizontal);
    mSplitter->setObjectName(QStringLiteral("mSplitter"));

    mainLayout->addWidget(mSplitter, 1);

    mTextAutogenerateResultWidget->setObjectName(QStringLiteral("mTextAutogenerateResultWidget"));

    mHistoryWidget->setObjectName(QStringLiteral("mHistoryWidget"));
    mSplitter->addWidget(mHistoryWidget);
    mSplitter->addWidget(mTextAutogenerateResultWidget);

    new KSplitterCollapserButton(mHistoryWidget, mSplitter);

    mTextAutoGenerateTextLineEditWidget->setObjectName(QStringLiteral("mTextAutoGenerateTextLineEditWidget"));
    mainLayout->addWidget(mTextAutoGenerateTextLineEditWidget);
    connect(mTextAutoGenerateTextLineEditWidget, &TextAutoGenerateTextLineEditWidget::editingFinished, this, &TextAutogenerateWidget::slotEditingFinished);

    connect(mHeaderWidget, &TextAutogenerateHeaderWidget::configChanged, this, &TextAutogenerateWidget::slotConfigureChanged);

    connect(TextAutoGenerateManager::self(), &TextAutoGenerateManager::sendMessageRequested, this, [this](const QString &str) {
        slotEditingFinished(str, {});
    });

    connect(TextAutoGenerateManager::self(), &TextAutoGenerateManager::askMessageRequested, this, [this](const QString &str) {
        slotAskMessageRequester(str);
    });

    connect(mTextAutoGenerateTextLineEditWidget, &TextAutoGenerateTextLineEditWidget::keyPressed, this, &TextAutogenerateWidget::keyPressedInLineEdit);
    connect(mTextAutogenerateResultWidget, &TextAutogenerateResultWidget::editMessageRequested, this, &TextAutogenerateWidget::slotEditMessage);
    connect(mTextAutogenerateResultWidget, &TextAutogenerateResultWidget::cancelRequested, this, &TextAutogenerateWidget::slotCancelRequest);
    connect(mTextAutogenerateResultWidget, &TextAutogenerateResultWidget::refreshAnswerRequested, this, &TextAutogenerateWidget::slotRefreshAnswer);
    connect(this, &TextAutogenerateWidget::stopEditingMode, mTextAutogenerateResultWidget, &TextAutogenerateResultWidget::editingFinished);
    connect(mHistoryWidget, &TextAutogenerateHistoryWidget::goToDiscussion, mTextAutogenerateResultWidget, &TextAutogenerateResultWidget::goToDiscussion);
    connect(TextAutoGenerateText::TextAutogenerateEngineLoader::self(), &TextAutoGenerateText::TextAutogenerateEngineLoader::noPluginsFound, this, [this]() {
        Q_EMIT noPluginsFound(i18n("No plugin found."));
    });
    loadEngine();
    readConfig();
}

TextAutogenerateWidget::~TextAutogenerateWidget()
{
    if (mTextAutogeneratePlugin) {
        mTextAutogeneratePlugin->cancelRequest({});
        mTextAutogeneratePlugin->deleteLater();
    }
    writeConfig();
}

void TextAutogenerateWidget::keyPressedInLineEdit(QKeyEvent *ev)
{
    const int key = ev->key();
    if (key == Qt::Key_Escape) {
        ev->accept();
        if (const QByteArray uuid = mTextAutoGenerateTextLineEditWidget->uuid(); !uuid.isEmpty()) {
            Q_EMIT stopEditingMode(uuid);
            mTextAutoGenerateTextLineEditWidget->setUuid({});
        }
    } else {
        mTextAutogenerateResultWidget->handleKeyPressEvent(ev);
    }
}

void TextAutogenerateWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("TextAutogenerateWidget"));
    group.writeEntry("mainSplitter", mSplitter->sizes());
}

void TextAutogenerateWidget::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("TextAutogenerateWidget"));
    const QList<int> size = {100, 400};

    mSplitter->setSizes(group.readEntry("mainSplitter", size));
}

QString TextAutogenerateWidget::textLineEdit() const
{
    return mTextAutoGenerateTextLineEditWidget->text();
}

void TextAutogenerateWidget::loadEngine()
{
    if (mTextAutogeneratePlugin) {
        disconnect(mTextAutogeneratePlugin);
        delete mTextAutogeneratePlugin;
        mTextAutogeneratePlugin = nullptr;
    }
    TextAutoGenerateText::TextAutogenerateEngineLoader::self()->loadPlugins();

    mTextAutogenerateClient =
        TextAutoGenerateText::TextAutogenerateEngineLoader::self()->createTextAutoGenerateTextClient(TextAutogenerateEngineUtil::loadEngine());
    if (!mTextAutogenerateClient) {
        const QString fallBackEngineName = TextAutoGenerateText::TextAutogenerateEngineLoader::self()->fallbackFirstEngine();
        if (!fallBackEngineName.isEmpty()) {
            mTextAutogenerateClient = TextAutoGenerateText::TextAutogenerateEngineLoader::self()->createTextAutoGenerateTextClient(fallBackEngineName);
        }
    }
    if (mTextAutogenerateClient) {
        mHeaderWidget->updateEngineName(TextAutoGenerateText::TextAutogenerateEngineLoader::self()->generateDisplayName(mTextAutogenerateClient));
        mTextAutogeneratePlugin = mTextAutogenerateClient->createTextAutogeneratePlugin();
        connect(mTextAutogeneratePlugin, &TextAutoGenerateText::TextAutoGenerateTextPlugin::finished, this, &TextAutogenerateWidget::slotAutogenerateFinished);
        connect(mTextAutogeneratePlugin,
                &TextAutoGenerateText::TextAutoGenerateTextPlugin::errorOccurred,
                this,
                &TextAutogenerateWidget::slotAutogenerateFailed);
        connect(mTextAutogeneratePlugin, &TextAutoGenerateText::TextAutoGenerateTextPlugin::initializedDone, this, &TextAutogenerateWidget::slotInitializeDone);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to create client" << TextAutogenerateEngineUtil::loadEngine();
    }
}

void TextAutogenerateWidget::slotConfigureChanged()
{
    loadEngine();
}

void TextAutogenerateWidget::slotEditingFinished(const QString &str, const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        mTextAutogeneratePlugin->sendMessage(str);
    } else {
        mTextAutogeneratePlugin->editMessage(uuid, str);
    }
    mTextAutogenerateResultWidget->editingFinished(uuid);
}

void TextAutogenerateWidget::slotAutogenerateFinished(const TextAutoGenerateMessage &msg)
{
    qDebug() << " TextAutogenerateWidget::slotAutogenerateFinished " << msg;
    // mTextAutogenerateResultWidget->addMessage(msg);
}

void TextAutogenerateWidget::slotAutogenerateFailed(const QString &errorMessage)
{
    qDebug() << " TextAutogenerateWidget::slotAutogenerateFailed " << errorMessage;
    Q_EMIT pluginBroken(errorMessage);
}

void TextAutogenerateWidget::slotEditMessage(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    const QString messageStr = index.data(TextAutoGenerateMessagesModel::MessageRole).toString();
    mTextAutoGenerateTextLineEditWidget->setUuid(uuid);
    mTextAutoGenerateTextLineEditWidget->setText(messageStr);
}

void TextAutogenerateWidget::slotCancelRequest(const QByteArray &uuid)
{
    mTextAutogeneratePlugin->cancelRequest(uuid);
}

void TextAutogenerateWidget::slotRefreshAnswer(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    const QString messageStr = index.data(TextAutoGenerateMessagesModel::MessageRole).toString();
    mTextAutogeneratePlugin->editMessage(uuid, messageStr);
}

void TextAutogenerateWidget::slotInitializeDone()
{
    mPluginWasInitialized = true;
    for (const auto &str : std::as_const(mAskMessageList)) {
        slotEditingFinished(str, {});
    }
    mAskMessageList.clear();
}

void TextAutogenerateWidget::slotAskMessageRequester(const QString &str)
{
    if (!mPluginWasInitialized) {
        mAskMessageList.append(str);
    } else {
        slotEditingFinished(str, {});
    }
}

#include "moc_textautogeneratewidget.cpp"
