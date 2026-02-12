/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "config-textautogeneratetext.h"
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
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
class TextAutoGenerateTextToSpeechEnqueueManager;
class TextAutoGenerateFileCache;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateManager
 * \brief The TextAutoGenerateManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateManager
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
        Cloud = 2048
    };
    Q_DECLARE_FLAGS(Categories, Category)
    Q_FLAG(Categories)

    struct TEXTAUTOGENERATETEXT_EXPORT AskMessageInfo {
        QString message;
        QStringList attachments;
        QList<QByteArray> tools;
        [[nodiscard]] bool isValid() const;
    };

    /*!
     * Constructs a new TextAutoGenerateManager object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateManager(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateManager object.
     */
    ~TextAutoGenerateManager() override;

    /*!
     * Sends a message to the text generator with the given parameters.
     * \param info The AskMessageInfo containing the message and settings
     */
    void ask(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info);

    /*!
     * Loads the chat history from the database.
     */
    void loadHistory();

    /*!
     * Returns whether archived chats are shown.
     * \return true if archived chats are shown, false otherwise
     */
    [[nodiscard]] bool showArchived() const;
    /*!
     * Sets whether archived chats should be shown.
     * \param newShowArchived true to show archived chats, false to hide them
     */
    void setShowArchived(bool newShowArchived);

    /*!
     * Returns the chats model.
     * \return A pointer to the TextAutoGenerateChatsModel
     */
    [[nodiscard]] TextAutoGenerateChatsModel *textAutoGenerateChatsModel() const;
    /*!
     * Returns the engine loader.
     * \return A pointer to the TextAutoGenerateEngineLoader
     */
    [[nodiscard]] TextAutoGenerateEngineLoader *textAutoGenerateEngineLoader() const;
    /*!
     * Loads the text generation engine.
     */
    void loadEngine();

    /*!
     * Generates a display name for the current engine.
     * \return The engine display name as a QString
     */
    [[nodiscard]] QString generateEngineDisplayName() const;

    /*!
     * Returns the text auto generate plugin.
     * \return A pointer to the TextAutoGenerateTextPlugin
     */
    [[nodiscard]] TextAutoGenerateTextPlugin *textAutoGeneratePlugin() const;

    /*!
     * Adds a message to a chat.
     * \param chatId The ID of the chat
     * \param msg The message to add
     */
    void addMessage(const QByteArray &chatId, const TextAutoGenerateMessage &msg);
    /*!
     * Refreshes an answer in a chat.
     * \param chatId The ID of the chat
     * \param uuid The UUID of the message to refresh
     * \return The model index of the refreshed message
     */
    [[nodiscard]] QModelIndex refreshAnswer(const QByteArray &chatId, const QByteArray &uuid) const;

    /*!
     * Returns the ID of the current chat.
     * \return The current chat ID as a QByteArray
     */
    [[nodiscard]] QByteArray currentChatId() const;
    /*!
     * Sets the current chat ID.
     * \param newCurrentChatId The chat ID to set
     */
    void setCurrentChatId(const QByteArray &newCurrentChatId);

    /*!
     * Returns the messages model for a specific chat.
     * \param chatId The ID of the chat
     * \return A pointer to the TextAutoGenerateMessagesModel
     */
    [[nodiscard]] TextAutoGenerateMessagesModel *messagesModelFromChatId(const QByteArray &chatId) const;
    /*!
     * Creates a new chat.
     * \param title The title of the new chat (optional)
     */
    void createNewChat(const QString &title = {});
    /*!
     * Replaces the content of a message in a chat.
     * \param chatId The ID of the chat
     * \param uuid The UUID of the message
     * \param content The new response content
     * \param attachementInfoList List of attachment information
     */
    void replaceContent(const QByteArray &chatId,
                        const QByteArray &uuid,
                        const TextAutoGenerateText::TextAutoGenerateReply::Response &content,
                        const QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachementInfoList);
    /*!
     * Changes the in-progress status of a message.
     * \param chatId The ID of the chat
     * \param uuid The UUID of the message
     * \param inProgress true if processing, false otherwise
     */
    void changeInProgress(const QByteArray &chatId, const QByteArray &uuid, bool inProgress);
    /*!
     * Removes a discussion (chat) from the database.
     * \param chatId The ID of the chat to remove
     */
    void removeDiscussion(const QByteArray &chatId);
    /*!
     * Cancels an ongoing request.
     * \param chatId The ID of the chat
     * \param index The model index of the message
     * \return true if the request was cancelled, false otherwise
     */
    [[nodiscard]] bool cancelRequest(const QByteArray &chatId, const QModelIndex &index);

    /*!
     * Changes the favorite status of a chat.
     * \param chatId The ID of the chat
     * \param favorite true to mark as favorite, false to unmark
     */
    void changeFavoriteHistory(const QByteArray &chatId, bool favorite);
    /*!
     * Archives or unarchives a discussion.
     * \param chatId The ID of the chat
     * \param archive true to archive, false to unarchive
     */
    void archiveDiscussion(const QByteArray &chatId, bool archive);
    /*!
     * Checks if a chat is marked as favorite.
     * \param chatId The ID of the chat
     * \return true if the chat is favorite, false otherwise
     */
    [[nodiscard]] bool chatIsFavorite(const QByteArray &chatId) const;

    /*!
     * Searches for text in the database.
     * \param searchText The text to search for
     * \return A list of matching TextAutoGenerateSearchMessage objects
     */
    [[nodiscard]] QList<TextAutoGenerateSearchMessage> searchTextInDatabase(const QString &searchText);
    /*!
     * Checks the current chat and updates its state.
     */
    void checkCurrentChat();
    /*!
     * Navigates to a specific message in a chat.
     * \param chatId The ID of the chat
     * \param messageId The ID of the message to navigate to
     */
    void goToMessage(const QByteArray &chatId, const QByteArray &messageId);
    /*!
     * Sends a message to the assistant.
     * \param msg The message to send
     */
    void askToAssistant(const QString &msg);
    /*!
     * Checks if a chat is currently processing.
     * \param chatId The ID of the chat
     * \return true if the chat is in progress, false otherwise
     */
    [[nodiscard]] bool chatInProgress(const QByteArray &chatId) const;
    /*!
     * Returns whether chat data should be saved in the database.
     * \return true if saving is enabled, false otherwise
     */
    [[nodiscard]] bool saveInDatabase() const;
    /*!
     * Sets whether chat data should be saved in the database.
     * \param newSaveInDatabase true to enable saving, false to disable
     */
    void setSaveInDatabase(bool newSaveInDatabase);

    /*!
     * Returns the instances manager.
     * \return A pointer to the TextAutoGenerateTextInstancesManager
     */
    [[nodiscard]] TextAutoGenerateTextInstancesManager *textAutoGenerateTextInstancesManager() const;

    /*!
     * Returns the chat settings.
     * \return A pointer to the TextAutoGenerateChatSettings
     */
    [[nodiscard]] TextAutoGenerateChatSettings *textAutoGenerateChatSettings() const;

    /*!
     * Removes a message from a chat.
     * \param chatId The ID of the chat
     * \param uuid The UUID of the message to remove
     */
    void removeMessage(const QByteArray &chatId, const QByteArray &uuid);

    /*!
     * Returns the system prompt.
     * \return The system prompt as a QString
     */
    [[nodiscard]] QString systemPrompt() const;
    /*!
     * Sets the system prompt.
     * \param newSystemPrompt The system prompt to set
     */
    void setSystemPrompt(const QString &newSystemPrompt);

    /*!
     * Returns whether the plugin has been initialized.
     * \return true if the plugin was initialized, false otherwise
     */
    [[nodiscard]] bool pluginWasInitialized() const;
    /*!
     * Sets the plugin initialization status.
     * \param newPluginWasInitialized true if initialized, false otherwise
     */
    void setPluginWasInitialized(bool newPluginWasInitialized);

    /*!
     * Switches to a chat by name.
     * \param chatName The name of the chat to switch to
     */
    void switchToChat(const QString &chatName);

    /*!
     * Converts a category enum value to a localized string.
     * \param cat The Category enum value
     * \return The localized category name as a QString
     */
    [[nodiscard]] static QString convertCategoryToI18n(TextAutoGenerateManager::Category cat);
    /*!
     * Converts a string to the corresponding Category enum value.
     * \param str The category string to convert
     * \return The corresponding Category enum value
     */
    [[nodiscard]] static TextAutoGenerateManager::Category convertStringToCategory(const QString &str);

    /*!
     * Resets the current chat ID.
     */
    void resetCurrentChatId();

    /*!
     * Saves the current chat to the database.
     * \param chatId The ID of the chat to save
     */
    void saveCurrentChatInDataBase(const QByteArray &chatId);
    /*!
     * Switches to a chat by ID.
     * \param chatId The ID of the chat to switch to
     */
    void switchToChatId(const QByteArray &chatId);
    /*!
     * Returns a list of all chat names.
     * \return A list of chat names as QStringList
     */
    [[nodiscard]] QStringList chatsList() const;
    /*!
     * Calls tools for a message.
     * \param chatId The ID of the chat
     * \param uuid The UUID of the message
     * \param info The tool call argument information
     */
    void callTools(const QByteArray &chatId, const QByteArray &uuid, const QList<TextAutoGenerateReply::ToolCallArgumentInfo> &info);

    /*!
     * Returns whether text-to-speech is enabled.
     * \return true if text-to-speech is enabled, false otherwise
     */
    [[nodiscard]] bool enableTextToSpeech() const;
    /*!
     * Sets whether text-to-speech should be enabled.
     * \param newEnableTextToSpeech true to enable, false to disable
     */
    void setEnableTextToSpeech(bool newEnableTextToSpeech);

#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    /*!
     * Returns the text-to-speech enqueue manager.
     * \return A pointer to the TextAutoGenerateTextToSpeechEnqueueManager
     */
    [[nodiscard]] TextAutoGenerateTextToSpeechEnqueueManager *textAutoGenerateTextToSpeechEnqueueManager() const;
#endif

    /*!
     * Returns whether debug mode is enabled.
     * \return true if debug mode is enabled, false otherwise
     */
    [[nodiscard]] bool debug() const;
    /*!
     * Sets whether debug mode should be enabled.
     * \param newDebug true to enable, false to disable
     */
    void setDebug(bool newDebug);

    /*!
     * Returns the database manager.
     * \return A pointer to the TextAutoGenerateLocalDatabaseManager
     */
    [[nodiscard]] TextAutoGenerateLocalDatabaseManager *databaseManager() const;

    /*!
     * Generates a temporary file path for an attachment.
     * \param attachmentId The ID of the attachment
     * \return The file path as a QString
     */
    [[nodiscard]] QString generateAttachmentTemporaryFile(const QByteArray &attachmentId) const;

    /*!
     * \brief importChat This method allows to import list of message
     * \param title the title of chat
     * \param msgs list of messages
     */
    void importChat(const QString &title, const QList<TextAutoGenerateText::TextAutoGenerateMessage> &msgs);

    /*!
     * \brief duplicateChat This method duplicates chats and messages
     * \param chatId
     */
    void duplicateChat(const QByteArray &chatId);
Q_SIGNALS:
    /*!
     * Emitted when a message should be sent.
     */
    void sendMessageRequested(const QString &str);
    /*!
     * Emitted when a message should be asked from the assistant.
     */
    void askMessageRequested(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info);
    /*!
     * Emitted when all plugins have been initialized.
     */
    void pluginsInitializedDone();
    /*!
     * Emitted when a download error occurs.
     */
    void downloadErrorOccured(const QString &msg);
    /*!
     * Emitted when the current chat ID changes.
     */
    void currentChatIdChanged();
    /*!
     * Emitted when the archive visibility changes.
     */
    void showArchiveChanged();
    /*!
     * Emitted to show a specific message by ID.
     */
    void showMessageId(const QByteArray &msgId);
    /*!
     * Emitted when the chat processing status changes.
     */
    void chatInProgressChanged(bool inProgress);
    /*!
     * Emitted when new instances need to be added.
     */
    void needToAddInstances();
    /*!
     * Emitted when the configuration changes.
     */
    void configChanged();
    /*!
     * Emitted when the engine has finished loading.
     */
    void loadEngineDone();
    /*!
     * Emitted when the font size changes.
     */
    void fontSizeChanged();
    /*!
     * Emitted when a model download finishes.
     */
    void downloadModelFinished(const QString &modelName);
    /*!
     * Emitted when an answer has been generated.
     */
    void answerGeneratedDone(const QString &question);
    /*!
     * Emitted when the chat list changes.
     */
    void chatListChanged(const QString &id);
    /*!
     * Emitted when the model list changes.
     */
    void modelListChanged(const QString &id);
    /*!
     * Emitted when a tool is being processed.
     */
    void toolInProgress(const QString &info);
    /*!
     * Emitted when the number of search strings changes.
     */
    void numberOfSearchStringChanged(int number);
    /*!
     * Emitted when the current model changes.
     */
    void currentModelChanged();
    /*!
     * Emitted when Ollama startup is requested.
     */
    void startOllamaRequested();
    /*!
     * Emitted when the Ollama process state changes.
     */
    void ollamaProcessOk(bool state);
    /*!
     * Emitted when Ollama fails.
     */
    void ollamaFailed();

    /*!
     * Emitted when a network error occurs.
     */
    void errorOccurred(QNetworkReply::NetworkError e);

private Q_SLOTS:
    void slotChatListChanged(const QString &id);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAboutToSynthesizeChanged(qsizetype previousId, qsizetype currentId);
    TEXTAUTOGENERATETEXT_NO_EXPORT void checkInitializedMessagesModel();
    TEXTAUTOGENERATETEXT_NO_EXPORT void changeChatInPogressStatus(const QByteArray &chatId, bool inProgress);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotPluginFinished(const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &info);
    TextAutoGenerateChatsModel *const mTextAutoGenerateChatsModel;
    std::unique_ptr<TextAutoGenerateLocalDatabaseManager> mDatabaseManager;
    std::unique_ptr<TextAutoGenerateChatSettings> const mTextAutoGenerateChatSettings;
    std::unique_ptr<TextAutoGenerateFileCache> const mTextAutoGenerateFileCache;
    TextAutoGenerateTextInstancesManager *const mTextAutoGenerateTextInstancesManager;
    TextAutoGenerateSettings *const mTextAutoGenerateSettings;
#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    TextAutoGenerateTextToSpeechEnqueueManager *const mTextAutoGenerateTextToSpeechEnqueueManager;
#endif
    QByteArray mCurrentChatId;
    QByteArray mSwitchToChatId;
    QString mSwitchToChatName;
    bool mShowArchived = false;
    bool mSaveInDatabase = true;
    bool mPluginWasInitialized = false;
    bool mDebug = false;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &t);
