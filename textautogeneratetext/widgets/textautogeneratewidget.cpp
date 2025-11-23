/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidget.h"
#include "core/textautogeneratechatsettings.h"

#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextclient.h"
#include "core/textautogeneratetextplugin.h"
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
#include <QSplitter>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
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
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});
    mainLayout->setSpacing(0);
    mHeaderWidget->setObjectName(u"mHeaderWidget"_s);
    mainLayout->addWidget(mHeaderWidget);

    mSplitter->setOrientation(Qt::Horizontal);
    mSplitter->setObjectName(u"mSplitter"_s);

    mainLayout->addWidget(mSplitter, 1);

    mTextAutoGenerateResultWidget->setObjectName(u"mTextAutoGenerateResultWidget"_s);

    mHistoryWidget->setObjectName(u"mHistoryWidget"_s);
    mSplitter->addWidget(mHistoryWidget);
    mSplitter->addWidget(mTextAutoGenerateResultWidget);

    new KSplitterCollapserButton(mHistoryWidget, mSplitter);

    mTextAutoGenerateTextLineEditWidget->setObjectName(u"mTextAutoGenerateTextLineEditWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateTextLineEditWidget);
    connect(mTextAutoGenerateTextLineEditWidget, &TextAutoGenerateTextLineEditWidget::editingFinished, this, &TextAutoGenerateWidget::slotEditingFinished);

    connect(mHeaderWidget, &TextAutoGenerateHeaderWidget::searchText, this, &TextAutoGenerateWidget::slotQuickSearchText);
    connect(mTextAutoGenerateResultWidget,
            &TextAutoGenerateResultWidget::closeSearchBarRequested,
            mHeaderWidget,
            &TextAutoGenerateHeaderWidget::slotCloseQuickSearchRequested);
    if (mManager) {
        connect(mHeaderWidget, &TextAutoGenerateHeaderWidget::addNewChat, this, [this]() {
            mManager->createNewChat();
        });
        connect(mManager, &TextAutoGenerateManager::sendMessageRequested, this, [this](const QString &str) {
            slotEditingFinished(str, {}, {}, {}); // TODO use tools list ?
        });

        connect(mManager, &TextAutoGenerateManager::askMessageRequested, this, [this](const QString &str) {
            slotAskMessageRequester(str);
        });

        connect(mManager, &TextAutoGenerateManager::currentChatIdChanged, this, [this]() {
            mTextAutoGenerateTextLineEditWidget->setEnabled(lineEditWidgetEnabledState());
            mHeaderWidget->slotCloseQuickSearchRequested();
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
            const QString text = mTextAutoGenerateTextLineEditWidget->text();
            const int position = mTextAutoGenerateResultWidget->scrollbarPosition();
            const QList<QByteArray> activatedTools = mTextAutoGenerateTextLineEditWidget->activatedTools();
            if (text.isEmpty() && (position == mTextAutoGenerateResultWidget->scrollbarPositionMaximum()) && activatedTools.isEmpty()) {
                mManager->textAutoGenerateChatSettings()->remove(mManager->currentChatId());
            } else {
                const TextAutoGenerateChatSettings::PendingTypedInfo chatSettingSave{
                    .text = text,
                    .scrollbarPosition = position,
                    .tools = activatedTools,
                };
                mManager->textAutoGenerateChatSettings()->add(mManager->currentChatId(), chatSettingSave);
            }
            mManager->setCurrentChatId(chatId);
            const TextAutoGenerateChatSettings::PendingTypedInfo chatSettingRestore = mManager->textAutoGenerateChatSettings()->value(chatId);
            if (chatSettingRestore.isValid()) {
                mTextAutoGenerateTextLineEditWidget->setText(chatSettingRestore.text);
                mTextAutoGenerateResultWidget->setScrollbarPosition(chatSettingRestore.scrollbarPosition);
                mTextAutoGenerateTextLineEditWidget->setActivatedTools(chatSettingRestore.tools);
            } else {
                mTextAutoGenerateTextLineEditWidget->setText({});
                mTextAutoGenerateResultWidget->scrollToBottom();
                mTextAutoGenerateTextLineEditWidget->setActivatedTools({});
            }
        });
        connect(mManager->textAutoGenerateEngineLoader(), &TextAutoGenerateText::TextAutoGenerateEngineLoader::noPluginsFound, this, [this]() {
            Q_EMIT noPluginsFound(i18n("No plugin found."));
        });
        connect(mHeaderWidget, &TextAutoGenerateHeaderWidget::changeFavoriteRequested, this, [this](bool checked) {
            mManager->changeFavoriteHistory(mManager->currentChatId(), checked);
        });

        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::errorOccured, this, &TextAutoGenerateWidget::slotAutogenerateFailed);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::needToAddInstances, this, &TextAutoGenerateWidget::needToAddInstances);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::pluginsInitializedDone, this, [this]() {
            slotInitializeDone();
            mHeaderWidget->setModelList(mManager->textAutoGeneratePlugin()->models());
            Q_EMIT pluginInitialized();
        });
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
            mTextAutoGenerateTextLineEditWidget->setText({});
        }
    } else {
        mTextAutoGenerateResultWidget->handleKeyPressEvent(ev);
    }
}

void TextAutoGenerateWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), u"TextAutoGenerateWidget"_s);
    group.writeEntry("mainSplitter", mSplitter->sizes());
    if (mManager && !mManager->currentChatId().isEmpty()) {
        group.writeEntry("currentChatId", mManager->currentChatId());
    }
}

void TextAutoGenerateWidget::readConfig()
{
    const KConfigGroup group(KSharedConfig::openStateConfig(), u"TextAutoGenerateWidget"_s);
    const QList<int> size = {100, 400};

    mSplitter->setSizes(group.readEntry("mainSplitter", size));
    if (mManager) {
        mManager->switchToChatId(group.readEntry("currentChatId", QByteArray()));
    }
}

QString TextAutoGenerateWidget::textLineEdit() const
{
    return mTextAutoGenerateTextLineEditWidget->text();
}

void TextAutoGenerateWidget::loadEngine()
{
    if (mManager) {
        mManager->loadEngine();
        mManager->loadHistory();
    }
}

void TextAutoGenerateWidget::slotEditingFinished(const QString &str,
                                                 const QByteArray &uuid,
                                                 const QList<QByteArray> &lstTools,
                                                 const QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachmentInfoList)
{
    mManager->checkCurrentChat();
    if (uuid.isEmpty()) {
        const TextAutoGenerateText::TextAutoGenerateTextPlugin::EditSendInfo info = {.message = str,
                                                                                     .messageUuid = {},
                                                                                     .chatId = mManager->currentChatId(),
                                                                                     .tools = lstTools,
                                                                                     .attachmentInfoList = attachmentInfoList};
        mManager->textAutoGeneratePlugin()->sendMessage(info);
    } else {
        const TextAutoGenerateText::TextAutoGenerateTextPlugin::EditSendInfo info = {.message = str,
                                                                                     .messageUuid = uuid,
                                                                                     .chatId = mManager->currentChatId(),
                                                                                     .tools = lstTools,
                                                                                     .attachmentInfoList = attachmentInfoList};
        mManager->textAutoGeneratePlugin()->editMessage(info);
    }
    mTextAutoGenerateResultWidget->editingFinished(uuid);
}

void TextAutoGenerateWidget::slotAutogenerateFailed(const QString &errorMessage)
{
    qDebug() << " TextAutoGenerateWidget::slotAutogenerateFailed " << errorMessage;
    Q_EMIT pluginBroken(errorMessage);
}

void TextAutoGenerateWidget::slotEditMessage(const QModelIndex &index, const QList<QByteArray> &tools)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    const QString messageStr = index.data(TextAutoGenerateMessagesModel::OriginalMessageRole).toString();
    mTextAutoGenerateTextLineEditWidget->setUuid(uuid);
    mTextAutoGenerateTextLineEditWidget->setText(messageStr);
    mTextAutoGenerateTextLineEditWidget->setActivatedTools(tools);
}

void TextAutoGenerateWidget::slotCancelRequest(const QByteArray &uuid)
{
    mManager->textAutoGeneratePlugin()->cancelRequest(uuid);
}

void TextAutoGenerateWidget::slotRefreshAnswer(const QByteArray &chatId, const QModelIndex &indexAnswer, const QList<QByteArray> &tools)
{
    const QByteArray uuid = indexAnswer.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    const QString messageStr = indexAnswer.data(TextAutoGenerateMessagesModel::OriginalMessageRole).toString();
    const TextAutoGenerateText::TextAutoGenerateTextPlugin::EditSendInfo info = {.message = messageStr,
                                                                                 .messageUuid = uuid,
                                                                                 .chatId = chatId,
                                                                                 .tools = tools,
                                                                                 .attachmentInfoList = {}};

    mManager->textAutoGeneratePlugin()->editMessage(info);
}

void TextAutoGenerateWidget::slotInitializeDone()
{
    for (const auto &str : std::as_const(mAskMessageList)) {
        slotEditingFinished(str, {}, {}, {});
    }
    mAskMessageList.clear();
    mHeaderWidget->setModelList(mManager->textAutoGeneratePlugin()->models());
}

void TextAutoGenerateWidget::slotAskMessageRequester(const QString &str)
{
    if (!mManager->pluginWasInitialized()) {
        mAskMessageList.append(str);
    } else {
        slotEditingFinished(str, {}, {}, {});
    }
}

void TextAutoGenerateWidget::slotQuickSearchText(bool enabled)
{
    mTextAutoGenerateResultWidget->quickSearchText(enabled);
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
