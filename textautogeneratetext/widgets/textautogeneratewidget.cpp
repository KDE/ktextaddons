/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidget.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextclient.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/common/textautogenerateresultwidget.h"
#include "widgets/common/textautogeneratetextlineeditwidget.h"
#include "widgets/textautogenerateheaderwidget.h"
#include "widgets/textautogeneratehistorywidget.h"
#include "widgets/textautogeneratesearchdialog.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KSplitterCollapserButton>
#include <QKeyEvent>
#include <QPointer>
#include <QSplitter>
#include <QVBoxLayout>
#include <qtimer.h>

using namespace TextAutoGenerateText;
TextAutoGenerateWidget::TextAutoGenerateWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateResultWidget(new TextAutoGenerateResultWidget(manager, this))
    , mTextAutoGenerateTextLineEditWidget(new TextAutoGenerateTextLineEditWidget(manager, this))
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

    connect(mHeaderWidget, &TextAutoGenerateHeaderWidget::searchText, this, &TextAutoGenerateWidget::slotSearchText);
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
            mTextAutoGenerateTextLineEditWidget->setEnabled(lineEditWidgetEnabledState());
        });
        mTextAutoGenerateTextLineEditWidget->setEnabled(lineEditWidgetEnabledState());
    }

    connect(mTextAutoGenerateTextLineEditWidget, &TextAutoGenerateTextLineEditWidget::keyPressed, this, &TextAutoGenerateWidget::keyPressedInLineEdit);
    connect(mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::editMessageRequested, this, &TextAutoGenerateWidget::slotEditMessage);
    connect(mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::cancelRequested, this, &TextAutoGenerateWidget::slotCancelRequest);
    connect(mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::refreshAnswerRequested, this, &TextAutoGenerateWidget::slotRefreshAnswer);
    connect(this, &TextAutoGenerateWidget::stopEditingMode, mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::editingFinished);
    if (mManager) {
        connect(mHistoryWidget, &TextAutoGenerateHistoryWidget::switchToChat, this, [this](const QByteArray &chatId) {
            mManager->setCurrentChatId(chatId);
            // TODO store info
        });
        connect(mManager->textAutoGenerateEngineLoader(), &TextAutoGenerateText::TextAutoGenerateEngineLoader::noPluginsFound, this, [this]() {
            Q_EMIT noPluginsFound(i18n("No plugin found."));
        });
        connect(mHeaderWidget, &TextAutoGenerateHeaderWidget::changeFavoriteRequested, this, [this](bool checked) {
            mManager->changeFavoriteHistory(mManager->currentChatId(), checked);
        });

        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::pluginsInitializedDone, this, &TextAutoGenerateWidget::slotInitializeDone);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::errorOccured, this, &TextAutoGenerateWidget::slotAutogenerateFailed);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::needToAddInstances, this, &TextAutoGenerateWidget::needToAddInstances);
    }
    readConfig();
}

TextAutoGenerateWidget::~TextAutoGenerateWidget()
{
    writeConfig();
}

bool TextAutoGenerateWidget::lineEditWidgetEnabledState() const
{
    return !mManager->currentChatId().isEmpty() && !mManager->showArchived() && !mManager->chatInProgress(mManager->currentChatId());
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
        mManager->loadEngine();
        mHeaderWidget->updateEngineName(mManager->generateEngineDisplayName());
        mManager->loadHistory();
    }
}

void TextAutoGenerateWidget::slotConfigureChanged()
{
    loadEngine();
}

void TextAutoGenerateWidget::slotEditingFinished(const QString &str, const QByteArray &uuid)
{
    mManager->checkCurrentChat();
    if (uuid.isEmpty()) {
        mManager->textAutoGeneratePlugin()->sendMessage(mManager->currentChatId(), str);
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

void TextAutoGenerateWidget::slotSearchText()
{
    if (!mSearchDialog) {
        mSearchDialog = new TextAutoGenerateSearchDialog(mManager, this);
        mSearchDialog->setAttribute(Qt::WA_DeleteOnClose, true);
        mSearchDialog->show();
    }
}

#include "moc_textautogeneratewidget.cpp"
