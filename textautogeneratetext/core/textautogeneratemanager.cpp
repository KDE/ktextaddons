/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"
#include "config-textautogeneratetext.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include "core/models/textautogeneratechatsmodel.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratesettings.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratechatsettings.h"
#include "textautogenerateengineloader.h"
#include "textautogeneratetextclient.h"
#include "textautogeneratetextcore_debug.h"
#include "textautogeneratetextinstancesmanager.h"
#include "textautogeneratetextplugin.h"

#if HAVE_KTEXTADDONS_TEXTAUTOGENERATE_DBUS_SUPPORT
#include "textautogeneratemanageradaptor.h"
#include <QDBusConnection>
#endif

#include <KLocalizedString>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

#if HAVE_KTEXTADDONS_TEXTAUTOGENERATE_DBUS_SUPPORT
static QString newDBusObjectName()
{
    static int s_count = 0;
    QString name(u"/TEXTAUTOGENERATEMANGER_TextAutoGenerateManager"_s);
    if (s_count++) {
        name += u'_';
        name += QString::number(s_count);
    }
    return name;
}
#endif
TextAutoGenerateManager::TextAutoGenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateChatsModel(new TextAutoGenerateChatsModel(this))
    , mDatabaseManager(new TextAutoGenerateLocalDatabaseManager)
    , mTextAutoGenerateChatSettings(new TextAutoGenerateChatSettings)
    , mTextAutoGenerateTextInstancesManager(new TextAutoGenerateTextInstancesManager(this, this))
    , mTextAutoGenerateSettings(new TextAutoGenerateSettings())
{
    mTextAutoGenerateChatsModel->setTextAutoGenerateChatSettings(mTextAutoGenerateChatSettings.get());
    // Load TextAutoGenerateTextToolPluginManager
    (void)TextAutoGenerateTextToolPluginManager::self();
#if HAVE_KTEXTADDONS_TEXTAUTOGENERATE_DBUS_SUPPORT
    new TextAutoGenerateManagerAdaptor(this);

    QDBusConnection dbus = QDBusConnection::sessionBus();
    const QString dbusPath = newDBusObjectName();
    setProperty("uniqueDBusPath", dbusPath);
    const QString dbusInterface = u"org.kde.textautogeneratetext.TextAutoGenerateManager"_s;
    dbus.registerObject(dbusPath, this);
    dbus.connect(QString(), QString(), dbusInterface, u"chatListChanged"_s, this, SLOT(slotChatListChanged(QString)));
#endif

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
    mTextAutoGenerateSettings->load();
}

TextAutoGenerateManager::~TextAutoGenerateManager()
{
    if (textAutoGeneratePlugin()) {
        textAutoGeneratePlugin()->cancelRequest({});
        textAutoGeneratePlugin()->deleteLater();
    }
    delete mTextAutoGenerateSettings;
}

TextAutoGenerateManager::Category TextAutoGenerateManager::convertStringToCategory(const QString &str)
{
    if (str == "tools"_L1) {
        return Category::Tools;
    } else if (str == "small"_L1) {
        return Category::Small;
    } else if (str == "medium"_L1) {
        return Category::Medium;
    } else if (str == "big"_L1) {
        return Category::Big;
    } else if (str == "huge"_L1) {
        return Category::Huge;
    } else if (str == "multilingual"_L1) {
        return Category::Multilingual;
    } else if (str == "code"_L1) {
        return Category::Code;
    } else if (str == "math"_L1) {
        return Category::Math;
    } else if (str == "vision"_L1) {
        return Category::Vision;
    } else if (str == "embedding"_L1) {
        return Category::Embedding;
    } else if (str == "reasoning"_L1) {
        return Category::Reasoning;
    }
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to convert " << str;
    return Category::Unknown;
}

QString TextAutoGenerateManager::convertCategoryToI18n(TextAutoGenerateManager::Category cat)
{
    switch (cat) {
    case Category::Unknown:
        return {};
    case Category::Tools:
        return i18n("Tools");
    case Category::Small:
        return i18n("Small");
    case Category::Medium:
        return i18n("Medium");
    case Category::Big:
        return i18n("Big");
    case Category::Huge:
        return i18n("Huge");
    case Category::Multilingual:
        return i18n("Multilingual");
    case Category::Code:
        return i18n("Code");
    case Category::Math:
        return i18n("Math");
    case Category::Vision:
        return i18n("Vision");
    case Category::Embedding:
        return i18n("Embedding");
    case Category::Reasoning:
        return i18n("Reasoning");
    }
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Missing translating Category " << static_cast<int>(cat);
    return {};
}

void TextAutoGenerateManager::askToAssistant(const QString &msg)
{
    if (textAutoGeneratePlugin()) {
        textAutoGeneratePlugin()->askToAssistant(msg);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to initialize plugin";
    }
}

void TextAutoGenerateManager::ask(const QString &msg)
{
    Q_EMIT askMessageRequested(msg);
}

void TextAutoGenerateManager::createNewChat(const QString &title)
{
    // Switch back to not archived list
    setShowArchived(false);
    TextAutoGenerateChat chat;
    const QByteArray chatId = QUuid::createUuid().toByteArray(QUuid::Id128);
    chat.setIdentifier(chatId);
    chat.setTitle(title);
    // we don't need to initialize it. (new chat => no data)
    chat.setInitialized(true);
    mTextAutoGenerateChatsModel->addChat(chat);
    if (mSaveInDatabase) {
        mDatabaseManager->insertOrUpdateChat(chat);
    }
    switchToChatId(chatId);
}

void TextAutoGenerateManager::switchToChatId(const QByteArray &chatId)
{
    if (!mPluginWasInitialized) {
        mSwitchToChatId = chatId;
    } else {
        setCurrentChatId(chatId);
    }
}

QStringList TextAutoGenerateManager::chatsList() const
{
    return mDatabaseManager->chatsList();
}

void TextAutoGenerateManager::replaceContent(const QByteArray &chatId,
                                             const QByteArray &uuid,
                                             const TextAutoGenerateText::TextAutoGenerateReply::Response &content)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        messagesModel->replaceContent(uuid, content.response); // TODO use tools
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

bool TextAutoGenerateManager::pluginWasInitialized() const
{
    return mPluginWasInitialized;
}

void TextAutoGenerateManager::setPluginWasInitialized(bool newPluginWasInitialized)
{
    mPluginWasInitialized = newPluginWasInitialized;
}

void TextAutoGenerateManager::switchToChat(const QString &chatName)
{
    if (!mPluginWasInitialized) {
        mSwitchToChatName = chatName;
    } else {
        setCurrentChatId(textAutoGenerateChatsModel()->chatIdFromChatName(chatName));
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

void TextAutoGenerateManager::callTools(const QByteArray &chatId, const QByteArray &uuid, const QList<TextAutoGenerateReply::ToolCallArgumentInfo> &info)
{
    // TODO
}

void TextAutoGenerateManager::changeInProgress(const QByteArray &chatId, const QByteArray &uuid, bool inProgress)
{
    auto messagesModel = messagesModelFromChatId(chatId);
    if (messagesModel) {
        messagesModel->changeInProgress(uuid, inProgress);
        changeChatInPogressStatus(chatId, inProgress);
        if (!inProgress) {
            // TODO Q_EMIT answerGeneratedDone();
        }
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
    const auto *plugin = textAutoGeneratePlugin();
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

QString TextAutoGenerateManager::systemPrompt() const
{
    return mTextAutoGenerateSettings->systemPrompt();
}

void TextAutoGenerateManager::setSystemPrompt(const QString &newSystemPrompt)
{
    mTextAutoGenerateSettings->setSystemPrompt(newSystemPrompt);
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
    if (mCurrentChatId.isEmpty() && mSwitchToChatId.isEmpty() && mSwitchToChatName.isEmpty()) {
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

void TextAutoGenerateManager::resetCurrentChatId()
{
    mCurrentChatId.clear();
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
                                if (roles.contains(TextAutoGenerateMessagesModel::MessageHtmlGeneratedRole)) {
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
        // delete textAutoGeneratePlugin();
    }
    mTextAutoGenerateTextInstancesManager->loadInstances();
    if (mTextAutoGenerateTextInstancesManager->isEmpty()) {
        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "We need to add instances";
        Q_EMIT needToAddInstances();
        return;
    }

    connect(textAutoGeneratePlugin(),
            &TextAutoGenerateText::TextAutoGenerateTextPlugin::downloadModelFinished,
            this,
            &TextAutoGenerateManager::downloadModelFinished);
    connect(textAutoGeneratePlugin(), &TextAutoGenerateText::TextAutoGenerateTextPlugin::errorOccurred, this, &TextAutoGenerateManager::errorOccured);
    connect(textAutoGeneratePlugin(), &TextAutoGenerateText::TextAutoGenerateTextPlugin::initializedDone, this, [this]() {
        setPluginWasInitialized(true);
        if (!mSwitchToChatId.isEmpty()) {
            setCurrentChatId(mSwitchToChatId);
            mSwitchToChatId.clear();
        }
        if (!mSwitchToChatName.isEmpty()) {
            switchToChat(mSwitchToChatName);
            mSwitchToChatName.clear();
        }
        Q_EMIT pluginsInitializedDone();
    });
    Q_EMIT loadEngineDone();
}

void TextAutoGenerateManager::saveCurrentChatInDataBase(const QByteArray &chatId)
{
    if (mSaveInDatabase) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Chat is already saved in database: chatId: " << chatId;
        return;
    }
    if (chatId.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Current Chat Id is empty it's a bug";
        return;
    }
    auto chat = mTextAutoGenerateChatsModel->chat(chatId);
    // Insert chat in database
    mDatabaseManager->insertOrUpdateChat(chat);

    auto model = mTextAutoGenerateChatsModel->messagesModel(chatId);
    if (model) {
        const auto msgs = model->messages();
        // Save each message in database
        for (const auto &m : msgs) {
            mDatabaseManager->insertOrReplaceMessage(chatId, m);
        }
    }
#if HAVE_KTEXTADDONS_TEXTAUTOGENERATE_DBUS_SUPPORT
    const QString ourIdentifier = u"%1/%2"_s.arg(QDBusConnection::sessionBus().baseService(), property("uniqueDBusPath").toString());
    Q_EMIT chatListChanged(ourIdentifier);
#endif
}

void TextAutoGenerateManager::slotChatListChanged([[maybe_unused]] const QString &id)
{
#if HAVE_KTEXTADDONS_TEXTAUTOGENERATE_DBUS_SUPPORT
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "TextAutoGenerateManager::slotChatListChanged :" << id;
    const QString ourIdentifier = u"%1/%2"_s.arg(QDBusConnection::sessionBus().baseService(), property("uniqueDBusPath").toString());
    if (id != ourIdentifier) {
        loadHistory();
    }
#endif
}

#include "moc_textautogeneratemanager.cpp"
