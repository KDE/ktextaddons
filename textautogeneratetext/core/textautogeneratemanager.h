/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
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
class TextAutoGenerateTextInstancesManager;

/**
 * @brief The TextAutoGenerateManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateManager : public QObject
{
    Q_OBJECT
public:
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
    void createNewChat();
    void replaceContent(const QByteArray &chatId, const QByteArray &uuid, const QString &content);
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

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void checkInitializedMessagesModel();
    TEXTAUTOGENERATETEXT_NO_EXPORT void changeChatInPogressStatus(const QByteArray &chatId, bool inProgress);
    TextAutoGenerateChatsModel *const mTextAutoGenerateChatsModel;
    std::unique_ptr<TextAutoGenerateLocalDatabaseManager> mDatabaseManager;
    std::unique_ptr<TextAutoGenerateChatSettings> const mTextAutoGenerateChatSettings;
    TextAutoGenerateTextInstancesManager *const mTextAutoGenerateTextInstancesManager;
    QByteArray mCurrentChatId;
    bool mShowArchived = false;
    bool mSaveInDatabase = true;
};
}
