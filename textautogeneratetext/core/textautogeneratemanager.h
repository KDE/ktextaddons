/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessagesModel;
class TextAutoGenerateLocalDatabaseManager;
class TextAutoGenerateChatsModel;
class TextAutoGenerateEngineLoader;
class TextAutoGenerateTextPlugin;
class TextAutoGenerateChatSettings;
class TextAutoGenerateSettings;
class TextAutoGenerateTextInstancesManager;
/**
 * @brief The TextAutoGenerateManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateManager : public QObject
{
    Q_OBJECT
public:
    enum class Category : uint16_t {
        Unknown = 0,
        Tools = 1,
        Small = 2,
        Medium = 4,
        Big = 8,
        Huge = 16,
        Multilingual = 32,
        Code = 64,
        Math = 128,
        Vision = 256,
        Embedding = 512,
        Reasoning = 1024,
    };
    Q_FLAGS(Category Categories)
    Q_DECLARE_FLAGS(Categories, Category)

    explicit TextAutoGenerateManager(QObject *parent = nullptr);
    ~TextAutoGenerateManager() override;

    void ask(const QString &msg);

    void loadHistory();

    [[nodiscard]] bool showArchived() const;
    void setShowArchived(bool newShowArchived);

    [[nodiscard]] TextAutoGenerateChatsModel *textAutoGenerateChatsModel() const;
    [[nodiscard]] TextAutoGenerateEngineLoader *textAutoGenerateEngineLoader() const;
    void loadEngine();

    [[nodiscard]] QString generateEngineDisplayName() const;

    [[nodiscard]] TextAutoGenerateTextPlugin *textAutoGeneratePlugin() const;

    void addMessage(const QByteArray &chatId, const TextAutoGenerateMessage &msg);
    [[nodiscard]] QModelIndex refreshAnswer(const QByteArray &chatId, const QByteArray &uuid) const;

    [[nodiscard]] QByteArray currentChatId() const;
    void setCurrentChatId(const QByteArray &newCurrentChatId);

    [[nodiscard]] TextAutoGenerateMessagesModel *messagesModelFromChatId(const QByteArray &chatId) const;
    void createNewChat(const QString &title = {});
    void replaceContent(const QByteArray &chatId, const QByteArray &uuid, const TextAutoGenerateText::TextAutoGenerateReply::Response &content);
    void changeInProgress(const QByteArray &chatId, const QByteArray &uuid, bool inProgress);
    void removeDiscussion(const QByteArray &chatId);
    [[nodiscard]] bool cancelRequest(const QByteArray &chatId, const QModelIndex &index);

    void changeFavoriteHistory(const QByteArray &chatId, bool favorite);
    void archiveDiscussion(const QByteArray &chatId, bool archive);
    [[nodiscard]] bool chatIsFavorite(const QByteArray &chatId) const;

    [[nodiscard]] QList<TextAutoGenerateSearchMessage> searchTextInDatabase(const QString &searchText);
    void checkCurrentChat();
    void goToMessage(const QByteArray &chatId, const QByteArray &messageId);
    void askToAssistant(const QString &msg);
    [[nodiscard]] bool chatInProgress(const QByteArray &chatId) const;
    [[nodiscard]] bool saveInDatabase() const;
    void setSaveInDatabase(bool newSaveInDatabase);

    [[nodiscard]] TextAutoGenerateTextInstancesManager *textAutoGenerateTextInstancesManager() const;

    [[nodiscard]] TextAutoGenerateChatSettings *textAutoGenerateChatSettings() const;

    void removeMessage(const QByteArray &chatId, const QByteArray &uuid);

    [[nodiscard]] QString systemPrompt() const;
    void setSystemPrompt(const QString &newSystemPrompt);

    [[nodiscard]] bool pluginWasInitialized() const;
    void setPluginWasInitialized(bool newPluginWasInitialized);

    void switchToChat(const QString &chatName);

    [[nodiscard]] static QString convertCategoryToI18n(TextAutoGenerateManager::Category cat);
    [[nodiscard]] static TextAutoGenerateManager::Category convertStringToCategory(const QString &str);

    void resetCurrentChatId();

    void saveCurrentChatInDataBase(const QByteArray &chatId);
    void switchToChatId(const QByteArray &chatId);
    [[nodiscard]] QStringList chatsList() const;
    void callTools(const QByteArray &chatId, const QByteArray &uuid, const QList<TextAutoGenerateReply::ToolCallArgumentInfo> &info);
Q_SIGNALS:
    void sendMessageRequested(const QString &str);
    void askMessageRequested(const QString &str);
    void pluginsInitializedDone();
    void errorOccured(const QString &msg);
    void currentChatIdChanged();
    void showArchiveChanged();
    void showMessageId(const QByteArray &msgId);
    void chatInProgressChanged(bool inProgress);
    void needToAddInstances();
    void configChanged();
    void loadEngineDone();
    void fontSizeChanged();
    void downloadModelFinished(const QString &modelName);
    void answerGeneratedDone(const QString &question);
    void chatListChanged(const QString &id);
    void modelListChanged(const QString &id);
    void toolInProgress(const QString &info);

private Q_SLOTS:
    void slotChatListChanged(const QString &id);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void checkInitializedMessagesModel();
    TEXTAUTOGENERATETEXT_NO_EXPORT void changeChatInPogressStatus(const QByteArray &chatId, bool inProgress);
    TEXTAUTOGENERATETEXT_NO_EXPORT void
    slotPluginFinished(const QString &str, const QByteArray &messageUuid, const QByteArray &chatId, const QByteArray &toolIdentifier);
    TextAutoGenerateChatsModel *const mTextAutoGenerateChatsModel;
    std::unique_ptr<TextAutoGenerateLocalDatabaseManager> mDatabaseManager;
    std::unique_ptr<TextAutoGenerateChatSettings> const mTextAutoGenerateChatSettings;
    TextAutoGenerateTextInstancesManager *const mTextAutoGenerateTextInstancesManager;
    TextAutoGenerateSettings *const mTextAutoGenerateSettings;
    QByteArray mCurrentChatId;
    QByteArray mSwitchToChatId;
    QString mSwitchToChatName;
    bool mShowArchived = false;
    bool mSaveInDatabase = true;
    bool mPluginWasInitialized = false;
};
}
