/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include "core/models/textautogeneratechatsmodel.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "textautogeneratechatsettings.h"
#include "textautogenerateengineloader.h"
#include "textautogeneratetextclient.h"
#include "textautogeneratetextcore_debug.h"
#include "textautogeneratetextinstancesmanager.h"
#include "textautogeneratetextplugin.h"

using namespace TextAutoGenerateText;
TextAutoGenerateManager::TextAutoGenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateChatsModel(new TextAutoGenerateChatsModel(this))
    , mDatabaseManager(new TextAutoGenerateLocalDatabaseManager)
    , mTextAutoGenerateChatSettings(new TextAutoGenerateChatSettings)
    , mTextAutoGenerateTextInstancesManager(new TextAutoGenerateTextInstancesManager(this, this))
{
    connect(mTextAutoGenerateChatsModel,
            &QAbstractItemModel::dataChanged,
            this,
            [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                if (mSaveInDatabase) {
                    if (roles.contains(TextAutoGenerateChatsModel::Title) || roles.contains(TextAutoGenerateChatsModel::Favorite)
                        || roles.contains(TextAutoGenerateChatsModel::Archived)) {
                        const QByteArray chatId = topLeft.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
                        const TextAutoGenerateChat chat = mTextAutoGenerateChatsModel->chat(chatId);
                        mDatabaseManager->insertOrUpdateChat(chat);
                    }
                }
            });
    connect(this, &TextAutoGenerateManager::configChanged, this, &TextAutoGenerateManager::loadEngine);
}

TextAutoGenerateManager::~TextAutoGenerateManager()
{
    if (textAutoGeneratePlugin()) {
        textAutoGeneratePlugin()->cancelRequest({});
        textAutoGeneratePlugin()->deleteLater();
    }
}

void TextAutoGenerateManager::askToAssistant(const QString &msg)
{
    if (textAutoGeneratePlugin()) {
        textAutoGeneratePlugin()->askToAssistant(msg);
    }
}

void TextAutoGenerateManager::ask(const QString &msg)
{
    Q_EMIT askMessageRequested(msg);
}

void TextAutoGenerateManager::createNewChat()
{
    // Switch back to not archived list
    setShowArchived(false);
    TextAutoGenerateChat chat;
    const QByteArray chatId = QUuid::createUuid().toByteArray(QUuid::Id128);
    chat.setIdentifier(chatId);
    // we don't need to initialize it. (new chat => no data)
    chat.setInitialized(true);
    mTextAutoGenerateChatsModel->addChat(chat);
    if (mSaveInDatabase) {
        mDatabaseManager->insertOrUpdateChat(chat);
    }
    setCurrentChatId(chatId);
}

void TextAutoGenerateManager::replaceContent(const QByteArray &chatId, const QByteArray &uuid, const QString &content)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        messagesModel->replaceContent(uuid, content);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to find model for " << chatId;
    }
}

bool TextAutoGenerateManager::chatInProgress(const QByteArray &chatId) const
{
    if (chatId.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " chatid is empty it's a bug!!!!";
        return false;
    }
    return textAutoGenerateChatsModel()->chatInProgress(chatId);
}

void TextAutoGenerateManager::changeChatInPogressStatus(const QByteArray &chatId, bool inProgress)
{
    textAutoGenerateChatsModel()->setChatInProgress(chatId, inProgress);
    if (chatId == currentChatId()) {
        Q_EMIT chatInProgressChanged(inProgress);
    }
}

TextAutoGenerateChatSettings *TextAutoGenerateManager::textAutoGenerateChatSettings() const
{
    return mTextAutoGenerateChatSettings.get();
}

TextAutoGenerateTextInstancesManager *TextAutoGenerateManager::textAutoGenerateTextInstancesManager() const
{
    return mTextAutoGenerateTextInstancesManager;
}

bool TextAutoGenerateManager::saveInDatabase() const
{
    return mSaveInDatabase;
}

void TextAutoGenerateManager::setSaveInDatabase(bool newSaveInDatabase)
{
    mSaveInDatabase = newSaveInDatabase;
}

void TextAutoGenerateManager::changeInProgress(const QByteArray &chatId, const QByteArray &uuid, bool inProgress)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        messagesModel->changeInProgress(uuid, inProgress);
        changeChatInPogressStatus(chatId, inProgress);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to find model for " << chatId;
    }
}

TextAutoGenerateChatsModel *TextAutoGenerateManager::textAutoGenerateChatsModel() const
{
    return mTextAutoGenerateChatsModel;
}

TextAutoGenerateEngineLoader *TextAutoGenerateManager::textAutoGenerateEngineLoader() const
{
    return mTextAutoGenerateTextInstancesManager->textAutoGenerateEngineLoader();
}

bool TextAutoGenerateManager::showArchived() const
{
    return mShowArchived;
}

void TextAutoGenerateManager::setShowArchived(bool newShowArchived)
{
    if (mShowArchived != newShowArchived) {
        mShowArchived = newShowArchived;
        Q_EMIT showArchiveChanged();
    }
}

void TextAutoGenerateManager::loadHistory()
{
    // Load chat from database
    const QList<TextAutoGenerateChat> chats = mDatabaseManager->loadChats();
    if (chats.isEmpty()) {
        createNewChat();
    } else {
        mTextAutoGenerateChatsModel->setChats(chats);
    }
}

QString TextAutoGenerateManager::generateEngineDisplayName() const
{
    QString displayName;
    auto plugin = textAutoGeneratePlugin();
    if (plugin) {
        displayName = QStringLiteral("%1 (%2)").arg(plugin->translatedPluginName(), TextAutoGenerateTextPlugin::convertEngineType(plugin->engineType()));
    }
    return displayName;
}

TextAutoGenerateTextPlugin *TextAutoGenerateManager::textAutoGeneratePlugin() const
{
    return mTextAutoGenerateTextInstancesManager->textAutoGeneratePlugin();
}

void TextAutoGenerateManager::removeMessage(const QByteArray &chatId, const QByteArray &uuid)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        const QList<QByteArray> lst = messagesModel->removeDiscussion(uuid);
        if (mSaveInDatabase) {
            for (const auto &b : lst) {
                mDatabaseManager->deleteMessage(chatId, QString::fromLatin1(b));
            }
        }
    }
}

bool TextAutoGenerateManager::cancelRequest(const QByteArray &chatId, const QModelIndex &index)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        changeChatInPogressStatus(chatId, false);
        return messagesModel->cancelRequest(index);
    }
    return false;
}

void TextAutoGenerateManager::archiveDiscussion(const QByteArray &chatId, bool archive)
{
    mTextAutoGenerateChatsModel->archiveDiscussion(chatId, archive);
}

void TextAutoGenerateManager::changeFavoriteHistory(const QByteArray &chatId, bool favorite)
{
    mTextAutoGenerateChatsModel->changeFavorite(chatId, favorite);
}

void TextAutoGenerateManager::removeDiscussion(const QByteArray &chatId)
{
    if (!chatId.isEmpty()) {
        mTextAutoGenerateChatsModel->removeDiscussion(chatId);
        if (mSaveInDatabase) {
            mDatabaseManager->deleteChat(chatId);
        }
    }
}

void TextAutoGenerateManager::addMessage(const QByteArray &chatId, const TextAutoGenerateMessage &msg)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        if (mSaveInDatabase) {
            mDatabaseManager->insertOrReplaceMessage(chatId, msg);
        }
        messagesModel->addMessage(msg);
        if (mSaveInDatabase) {
            // Update chat
            const TextAutoGenerateChat chat = mTextAutoGenerateChatsModel->chat(chatId);
            mDatabaseManager->insertOrUpdateChat(chat);
        }
    }
}

QModelIndex TextAutoGenerateManager::refreshAnswer(const QByteArray &chatId, const QByteArray &uuid) const
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        return messagesModel->refreshAnswer(uuid);
    }
    return {};
}

QByteArray TextAutoGenerateManager::currentChatId() const
{
    return mCurrentChatId;
}

void TextAutoGenerateManager::checkCurrentChat()
{
    if (mCurrentChatId.isEmpty()) {
        createNewChat();
    }
}

void TextAutoGenerateManager::goToMessage(const QByteArray &chatId, const QByteArray &messageId)
{
    const auto messagesModel = messagesModelFromChatId(chatId);
    if (!messagesModel) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to find channel" << chatId;
        return;
    }
    setCurrentChatId(chatId);
    setShowArchived(mTextAutoGenerateChatsModel->chatIsArchived(mCurrentChatId));
    Q_EMIT showMessageId(messageId);
}

bool TextAutoGenerateManager::chatIsFavorite(const QByteArray &chatId) const
{
    if (chatId.isEmpty()) {
        return false;
    }
    return mTextAutoGenerateChatsModel->chatIsFavorited(chatId);
}

QList<TextAutoGenerateSearchMessage> TextAutoGenerateManager::searchTextInDatabase(const QString &searchText)
{
    return mDatabaseManager->searchTextInDatabase(mTextAutoGenerateChatsModel->chatsId(), searchText);
}

void TextAutoGenerateManager::setCurrentChatId(const QByteArray &newCurrentChatId)
{
    if (mCurrentChatId != newCurrentChatId) {
        mCurrentChatId = newCurrentChatId;
        checkInitializedMessagesModel();
        Q_EMIT currentChatIdChanged();
    }
}

void TextAutoGenerateManager::checkInitializedMessagesModel()
{
    if (!mCurrentChatId.isEmpty()) {
        const QByteArray chatId = mCurrentChatId;
        if (!mTextAutoGenerateChatsModel->isInitialized(chatId)) {
            auto messagesModel = messagesModelFromChatId(chatId);
            if (messagesModel) {
                if (mSaveInDatabase) {
                    QList<TextAutoGenerateMessage> messages = mDatabaseManager->loadMessages(mCurrentChatId);
                    // Sort messages
                    std::sort(messages.begin(), messages.end(), [](const TextAutoGenerateMessage &left, const TextAutoGenerateMessage &right) {
                        if (left.dateTime() == right.dateTime()) {
                            if (left.sender() == TextAutoGenerateMessage::Sender::User) {
                                return true;
                            }
                        }
                        return left.dateTime() < right.dateTime();
                    });

                    messagesModel->setMessages(messages);
                    connect(messagesModel,
                            &QAbstractItemModel::dataChanged,
                            this,
                            [this, chatId, messagesModel](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                                if (roles.contains(TextAutoGenerateMessagesModel::MessageRole)) {
                                    const QByteArray uuid = topLeft.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
                                    const TextAutoGenerateMessage msg = messagesModel->message(uuid);
                                    mDatabaseManager->insertOrReplaceMessage(chatId, msg);
                                }
                                mTextAutoGenerateChatsModel->messagesChanged(chatId);
                            });
                }
                connect(messagesModel, &QAbstractItemModel::rowsRemoved, this, [this, chatId]() {
                    mTextAutoGenerateChatsModel->messagesChanged(chatId);
                });
                connect(messagesModel, &QAbstractItemModel::rowsInserted, this, [this, chatId]() {
                    mTextAutoGenerateChatsModel->messagesChanged(chatId);
                });
            }
            mTextAutoGenerateChatsModel->setInitialized(mCurrentChatId, true);
        }
    }
}

TextAutoGenerateMessagesModel *TextAutoGenerateManager::messagesModelFromChatId(const QByteArray &chatId) const
{
    if (chatId.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " chatid is empty it's a bug!!!!";
        return nullptr;
    }
    return textAutoGenerateChatsModel()->messagesModel(chatId);
}

void TextAutoGenerateManager::loadEngine()
{
    if (textAutoGeneratePlugin()) {
        disconnect(textAutoGeneratePlugin());
        delete textAutoGeneratePlugin();
    }
    mTextAutoGenerateTextInstancesManager->loadInstances();
    if (mTextAutoGenerateTextInstancesManager->isEmpty()) {
        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "We need to add instances";
        Q_EMIT needToAddInstances();
        return;
    }

    connect(textAutoGeneratePlugin(), &TextAutoGenerateText::TextAutoGenerateTextPlugin::errorOccurred, this, &TextAutoGenerateManager::errorOccured);
    connect(textAutoGeneratePlugin(),
            &TextAutoGenerateText::TextAutoGenerateTextPlugin::initializedDone,
            this,
            &TextAutoGenerateManager::pluginsInitializedDone);
    Q_EMIT loadEngineDone();
}
#include "moc_textautogeneratemanager.cpp"
