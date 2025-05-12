/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidget.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogenerateengineutil.h"
#include "core/textautogeneratemanager.h"
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
TextAutoGenerateWidget::TextAutoGenerateWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateResultWidget(new TextAutoGenerateResultWidget(manager, this))
    , mTextAutoGenerateTextLineEditWidget(new TextAutoGenerateTextLineEditWidget(this))
    , mSplitter(new QSplitter(this))
    , mHistoryWidget(new TextAutoGenerateHistoryWidget(manager, this))
    , mHeaderWidget(new TextAutoGenerateHeaderWidget(manager, this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
    mHeaderWidget->setObjectName(QStringLiteral("mHeaderWidget"));
    mainLayout->addWidget(mHeaderWidget);

    mSplitter->setOrientation(Qt::Horizontal);
    mSplitter->setObjectName(QStringLiteral("mSplitter"));

    mainLayout->addWidget(mSplitter, 1);

    mTextAutoGenerateResultWidget->setObjectName(QStringLiteral("mTextAutoGenerateResultWidget"));

    mHistoryWidget->setObjectName(QStringLiteral("mHistoryWidget"));
    mSplitter->addWidget(mHistoryWidget);
    mSplitter->addWidget(mTextAutoGenerateResultWidget);

    new KSplitterCollapserButton(mHistoryWidget, mSplitter);

    mTextAutoGenerateTextLineEditWidget->setObjectName(QStringLiteral("mTextAutoGenerateTextLineEditWidget"));
    mainLayout->addWidget(mTextAutoGenerateTextLineEditWidget);
    connect(mTextAutoGenerateTextLineEditWidget, &TextAutoGenerateTextLineEditWidget::editingFinished, this, &TextAutoGenerateWidget::slotEditingFinished);

    connect(mHeaderWidget, &TextAutoGenerateHeaderWidget::configChanged, this, &TextAutoGenerateWidget::slotConfigureChanged);

    if (mManager) {
        connect(mHeaderWidget, &TextAutoGenerateHeaderWidget::addNewChat, this, [this]() {
            mManager->createNewChat();
        });
        connect(mManager, &TextAutoGenerateManager::sendMessageRequested, this, [this](const QString &str) {
            slotEditingFinished(str, {});
        });

        connect(mManager, &TextAutoGenerateManager::askMessageRequested, this, [this](const QString &str) {
            slotAskMessageRequester(str);
        });

        connect(mManager, &TextAutoGenerateManager::currentChatIdChanged, this, [this]() {
            mTextAutoGenerateTextLineEditWidget->setEnabled(!mManager->currentChatId().isEmpty());
        });
        mTextAutoGenerateTextLineEditWidget->setEnabled(!mManager->currentChatId().isEmpty());
    }

    connect(mTextAutoGenerateTextLineEditWidget, &TextAutoGenerateTextLineEditWidget::keyPressed, this, &TextAutoGenerateWidget::keyPressedInLineEdit);
    connect(mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::editMessageRequested, this, &TextAutoGenerateWidget::slotEditMessage);
    connect(mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::cancelRequested, this, &TextAutoGenerateWidget::slotCancelRequest);
    connect(mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::refreshAnswerRequested, this, &TextAutoGenerateWidget::slotRefreshAnswer);
    connect(this, &TextAutoGenerateWidget::stopEditingMode, mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::editingFinished);
    if (mManager) {
        connect(mHistoryWidget, &TextAutoGenerateHistoryWidget::switchToChat, this, [this](const QByteArray &chatId) {
            mManager->setCurrentChatId(chatId);
        });
        connect(mManager->textAutoGenerateEngineLoader(), &TextAutoGenerateText::TextAutoGenerateEngineLoader::noPluginsFound, this, [this]() {
            Q_EMIT noPluginsFound(i18n("No plugin found."));
        });
    }
    loadEngine();
    readConfig();
}

TextAutoGenerateWidget::~TextAutoGenerateWidget()
{
    writeConfig();
}

void TextAutoGenerateWidget::keyPressedInLineEdit(QKeyEvent *ev)
{
    const int key = ev->key();
    if (key == Qt::Key_Escape) {
        ev->accept();
        if (const QByteArray uuid = mTextAutoGenerateTextLineEditWidget->uuid(); !uuid.isEmpty()) {
            Q_EMIT stopEditingMode(uuid);
            mTextAutoGenerateTextLineEditWidget->setUuid({});
        }
    } else {
        mTextAutoGenerateResultWidget->handleKeyPressEvent(ev);
    }
}

void TextAutoGenerateWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("TextAutoGenerateWidget"));
    group.writeEntry("mainSplitter", mSplitter->sizes());
}

void TextAutoGenerateWidget::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QStringLiteral("TextAutoGenerateWidget"));
    const QList<int> size = {100, 400};

    mSplitter->setSizes(group.readEntry("mainSplitter", size));
}

QString TextAutoGenerateWidget::textLineEdit() const
{
    return mTextAutoGenerateTextLineEditWidget->text();
}

void TextAutoGenerateWidget::loadEngine()
{
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::pluginsInitializedDone, this, &TextAutoGenerateWidget::slotInitializeDone);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::errorOccured, this, &TextAutoGenerateWidget::slotAutogenerateFailed);
        mManager->loadEngine();
        if (mManager->textAutoGenerateClient()) {
            mHeaderWidget->updateEngineName(mManager->generateEngineDisplayName());
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to create client" << TextAutoGenerateEngineUtil::loadEngine();
        }
    }
}

void TextAutoGenerateWidget::slotConfigureChanged()
{
    loadEngine();
}

void TextAutoGenerateWidget::slotEditingFinished(const QString &str, const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        mManager->textAutoGeneratePlugin()->sendMessage(str);
    } else {
        mManager->textAutoGeneratePlugin()->editMessage(mManager->currentChatId(), uuid, str);
    }
    mTextAutoGenerateResultWidget->editingFinished(uuid);
}

void TextAutoGenerateWidget::slotAutogenerateFailed(const QString &errorMessage)
{
    qDebug() << " TextAutoGenerateWidget::slotAutogenerateFailed " << errorMessage;
    Q_EMIT pluginBroken(errorMessage);
}

void TextAutoGenerateWidget::slotEditMessage(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    const QString messageStr = index.data(TextAutoGenerateMessagesModel::OriginalMessageRole).toString();
    mTextAutoGenerateTextLineEditWidget->setUuid(uuid);
    mTextAutoGenerateTextLineEditWidget->setText(messageStr);
}

void TextAutoGenerateWidget::slotCancelRequest(const QByteArray &uuid)
{
    mManager->textAutoGeneratePlugin()->cancelRequest(uuid);
}

void TextAutoGenerateWidget::slotRefreshAnswer(const QByteArray &chatId, const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    const QString messageStr = index.data(TextAutoGenerateMessagesModel::OriginalMessageRole).toString();
    mManager->textAutoGeneratePlugin()->editMessage(chatId, uuid, messageStr);
}

void TextAutoGenerateWidget::slotInitializeDone()
{
    mPluginWasInitialized = true;
    for (const auto &str : std::as_const(mAskMessageList)) {
        slotEditingFinished(str, {});
    }
    mAskMessageList.clear();
}

void TextAutoGenerateWidget::slotAskMessageRequester(const QString &str)
{
    if (!mPluginWasInitialized) {
        mAskMessageList.append(str);
    } else {
        slotEditingFinished(str, {});
    }
}

#include "moc_textautogeneratewidget.cpp"
