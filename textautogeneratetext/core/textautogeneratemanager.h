/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
    Q_DECLARE_FLAGS(Categories, Category)
    Q_FLAG(Categories)

    struct TEXTAUTOGENERATETEXT_EXPORT AskMessageInfo {
        QString message;
        QStringList attachments;
        QList<QByteArray> tools;
        [[nodiscard]] bool isValid() const;
    };

    explicit TextAutoGenerateManager(QObject *parent = nullptr);
    ~TextAutoGenerateManager() override;

    void ask(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info);

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
    void replaceContent(const QByteArray &chatId,
                        const QByteArray &uuid,
                        const TextAutoGenerateText::TextAutoGenerateReply::Response &content,
                        const QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachementInfoList);
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

    [[nodiscard]] bool enableTextToSpeech() const;
    void setEnableTextToSpeech(bool newEnableTextToSpeech);

#if HAVE_KTEXTADDONS_TEXT_TO_SPEECH_SUPPORT
    [[nodiscard]] TextAutoGenerateTextToSpeechEnqueueManager *textAutoGenerateTextToSpeechEnqueueManager() const;
#endif

    [[nodiscard]] bool debug() const;
    void setDebug(bool newDebug);

    [[nodiscard]] TextAutoGenerateLocalDatabaseManager *databaseManager() const;

    [[nodiscard]] QString generateAttachmentTemporaryFile() const;

Q_SIGNALS:
    void sendMessageRequested(const QString &str);
    void askMessageRequested(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info);
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
    void numberOfSearchStringChanged(int number);
    void currentModelChanged();
    void startOllamaRequested();
    void ollamaProcessOk(bool state);
    void ollamaFailed();

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
