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
#include "textautogenerateengineloader.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateManager::TextAutoGenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateMessagesModel(new TextAutoGenerateMessagesModel(this))
    , mTextAutoGenerateChatsModel(new TextAutoGenerateChatsModel(this))
    , mTextAutoGenerateEngineLoader(new TextAutoGenerateEngineLoader(this))
    , mDatabaseManager(new TextAutoGenerateLocalDatabaseManager)
{
}

TextAutoGenerateManager::~TextAutoGenerateManager()
{
    if (mTextAutoGeneratePlugin) {
        mTextAutoGeneratePlugin->cancelRequest({});
        mTextAutoGeneratePlugin->deleteLater();
    }
}

void TextAutoGenerateManager::ask(const QString &msg)
{
    Q_EMIT askMessageRequested(msg);
}

TextAutoGenerateMessagesModel *TextAutoGenerateManager::textAutoGenerateMessagesModel() const
{
    return mTextAutoGenerateMessagesModel;
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
    mShowArchived = newShowArchived;
}

void TextAutoGenerateManager::loadHistory()
{
    // Load chat from database
    const QList<TextAutoGenerateChat> chats = mDatabaseManager->loadChats();
    mTextAutoGenerateChatsModel->setChats(std::move(chats));
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

void TextAutoGenerateManager::addMessage(const TextAutoGenerateMessage &msg)
{
    // TODO add to database
    // TODO Use correct textAutoGenerateMessagesModel
    textAutoGenerateMessagesModel()->addMessage(msg);
}

QByteArray TextAutoGenerateManager::currentChatId() const
{
    return mCurrentChatId;
}

void TextAutoGenerateManager::setCurrentChatId(const QByteArray &newCurrentChatId)
{
    if (mCurrentChatId != newCurrentChatId) {
        mCurrentChatId = newCurrentChatId;
        Q_EMIT currentChatIdChanged();
    }
}

TextAutoGenerateMessagesModel *TextAutoGenerateManager::messagesModelFromChatId(const QByteArray &chatId)
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
