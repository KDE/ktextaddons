/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include "core/textautogeneratechatsmodel.h"
#include "core/textautogenerateengineutil.h"
#include "core/textautogeneratemessagesmodel.h"
#include "core/textautogeneratetextclient.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratechatsettings.h"
#include "textautogenerateengineloader.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateManager::TextAutoGenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateChatsModel(new TextAutoGenerateChatsModel(this))
    , mTextAutoGenerateEngineLoader(new TextAutoGenerateEngineLoader(this))
    , mDatabaseManager(new TextAutoGenerateLocalDatabaseManager)
    , mTextAutoGenerateChatSettings(new TextAutoGenerateChatSettings)
{
    connect(mTextAutoGenerateChatsModel,
            &QAbstractItemModel::dataChanged,
            this,
            [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                if (roles.contains(TextAutoGenerateChatsModel::Title) || roles.contains(TextAutoGenerateChatsModel::Favorite)
                    || roles.contains(TextAutoGenerateChatsModel::Archived)) {
                    const QByteArray chatId = topLeft.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
                    const TextAutoGenerateChat chat = mTextAutoGenerateChatsModel->chat(chatId);
                    mDatabaseManager->insertOrUpdateChat(chat);
                }
            });
}

TextAutoGenerateManager::~TextAutoGenerateManager()
{
    if (mTextAutoGeneratePlugin) {
        mTextAutoGeneratePlugin->cancelRequest({});
        mTextAutoGeneratePlugin->deleteLater();
    }
}

void TextAutoGenerateManager::askToAssistant(const QString &msg)
{
    if (mTextAutoGeneratePlugin) {
        mTextAutoGeneratePlugin->askToAssistant(msg);
    }
}

void TextAutoGenerateManager::ask(const QString &msg)
{
    Q_EMIT askMessageRequested(msg);
}

void TextAutoGenerateManager::createNewChat()
{
    TextAutoGenerateChat chat;
    const QByteArray chatId = QUuid::createUuid().toByteArray(QUuid::Id128);
    chat.setIdentifier(chatId);
    // we don't need to initialize it. (new chat => no data)
    chat.setInitialized(true);
    mTextAutoGenerateChatsModel->addChat(chat);
    mDatabaseManager->insertOrUpdateChat(chat);
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

void TextAutoGenerateManager::changeInProgress(const QByteArray &chatId, const QByteArray &uuid, bool inProgress)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        messagesModel->changeInProgress(uuid, inProgress);
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
    return mTextAutoGenerateEngineLoader;
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
        mTextAutoGenerateChatsModel->setChats(std::move(chats));
    }
}

QString TextAutoGenerateManager::generateEngineDisplayName() const
{
    return mTextAutoGenerateEngineLoader->generateDisplayName(mTextAutoGenerateClient);
}

TextAutoGenerateTextClient *TextAutoGenerateManager::textAutoGenerateClient() const
{
    return mTextAutoGenerateClient;
}

TextAutoGenerateTextPlugin *TextAutoGenerateManager::textAutoGeneratePlugin() const
{
    return mTextAutoGeneratePlugin;
}

bool TextAutoGenerateManager::cancelRequest(const QByteArray &chatId, const QModelIndex &index)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
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
        mDatabaseManager->deleteChat(chatId);
        setCurrentChatId({});
    }
}

void TextAutoGenerateManager::addMessage(const QByteArray &chatId, const TextAutoGenerateMessage &msg)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        mDatabaseManager->insertOrReplaceMessage(chatId, msg);
        messagesModel->addMessage(msg);
        // Update chat
        const TextAutoGenerateChat chat = mTextAutoGenerateChatsModel->chat(chatId);
        mDatabaseManager->insertOrUpdateChat(chat);
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
    auto messagesModel = messagesModelFromChatId(chatId);
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
    if (mTextAutoGeneratePlugin) {
        disconnect(mTextAutoGeneratePlugin);
        delete mTextAutoGeneratePlugin;
        mTextAutoGeneratePlugin = nullptr;
    }
    mTextAutoGenerateEngineLoader->loadPlugins();

    mTextAutoGenerateClient = mTextAutoGenerateEngineLoader->createTextAutoGenerateTextClient(TextAutoGenerateEngineUtil::loadEngine());
    if (!mTextAutoGenerateClient) {
        const QString fallBackEngineName = mTextAutoGenerateEngineLoader->fallbackFirstEngine();
        if (!fallBackEngineName.isEmpty()) {
            mTextAutoGenerateClient = mTextAutoGenerateEngineLoader->createTextAutoGenerateTextClient(fallBackEngineName);
        }
    }
    if (mTextAutoGenerateClient) {
        mTextAutoGeneratePlugin = mTextAutoGenerateClient->createTextAutoGeneratePlugin();
        mTextAutoGeneratePlugin->setManager(this);
        connect(mTextAutoGeneratePlugin, &TextAutoGenerateText::TextAutoGenerateTextPlugin::errorOccurred, this, &TextAutoGenerateManager::errorOccured);
        connect(mTextAutoGeneratePlugin,
                &TextAutoGenerateText::TextAutoGenerateTextPlugin::initializedDone,
                this,
                &TextAutoGenerateManager::pluginsInitializedDone);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to create client" << TextAutoGenerateEngineUtil::loadEngine();
    }
}
#include "moc_textautogeneratemanager.cpp"
