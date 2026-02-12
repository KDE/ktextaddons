/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <TextAutoGenerateText/TextAutoGenerateChat>

#include <QAbstractListModel>
namespace TextAutoGenerateText
{
class TextAutoGenerateChatSettings;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateChatsModel
 * \brief The TextAutoGenerateChatsModel class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateChatsModel
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChatRoles : uint16_t {
        Title = Qt::UserRole + 1,
        Archived,
        Favorite,
        Identifier,
        Section,
        InProgress,
        DateTime,
        HasPendingMessageTyped,
    };

    enum class SectionHistory : uint8_t {
        Favorite,
        Today,
        LessThanSevenDays,
        LessThanThirtyDays,
        Later,
        Unknown,
        NSections,
    };

    /*! Constructs a new TextAutoGenerateChatsModel with the given @p parent. */
    explicit TextAutoGenerateChatsModel(QObject *parent = nullptr);
    /*! Destroys the TextAutoGenerateChatsModel object. */
    ~TextAutoGenerateChatsModel() override;

    /*! Returns the number of rows in the model. */
    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    /*! Returns the data for the given @p index and @p role. */
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    /*! Sets the @p value for the given @p index and @p role. */
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*! Returns the flags for the given @p index. */
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    /*! Returns the chat with the given @p chatId, or an empty chat if not found. */
    [[nodiscard]] TextAutoGenerateChat chat(const QByteArray &chatId) const;

    /*! Returns all chats in the model. */
    [[nodiscard]] QList<TextAutoGenerateChat> chats() const;
    /*! Sets the chats to the given list of @p newMessages. */
    void setChats(const QList<TextAutoGenerateChat> &newMessages);

    /*! Adds the given @p chat to the model. */
    void addChat(const TextAutoGenerateChat &chat);
    /*! Returns the translated section name for the given @p sectionId. */
    [[nodiscard]] static QString sectionName(TextAutoGenerateChat::SectionHistory sectionId);

    /*! Returns the messages model for the chat with the given @p chatId. */
    [[nodiscard]] TextAutoGenerateMessagesModel *messagesModel(const QByteArray &chatId) const;

    /*!
     */
    [[nodiscard]] bool isInitialized(const QByteArray &chatId) const;

    /*!
     */
    void setInitialized(const QByteArray &chatId, bool state);

    /*! Notifies that messages have changed for the chat with the given @p chatId. */
    void messagesChanged(const QByteArray &chatId);

    /*! Removes the discussion (chat) with the given @p chatId. */
    void removeDiscussion(const QByteArray &chatId);

    /*! Sets the favorite status of the chat with the given @p chatId to @p favorite. */
    void changeFavorite(const QByteArray &chatId, bool favorite);

    /*! Archives or unarchives the discussion with the given @p chatId based on the @p favorite flag. */
    void archiveDiscussion(const QByteArray &chatId, bool favorite);

    /*! Returns whether the chat with the given @p chatId is marked as favorite. */
    [[nodiscard]] bool chatIsFavorited(const QByteArray &chatId) const;
    /*! Returns whether the chat with the given @p chatId is archived. */
    [[nodiscard]] bool chatIsArchived(const QByteArray &chatId) const;
    /*! Returns whether the chat with the given @p chatId is currently in progress. */
    [[nodiscard]] bool chatInProgress(const QByteArray &chatId) const;

    /*! Returns a list of all chat IDs in the model. */
    [[nodiscard]] QList<QByteArray> chatsId() const;

    /*! Sets the in-progress status of the chat with the given @p chatId to @p state. */
    void setChatInProgress(const QByteArray &chatId, bool state);

    /*! Returns the title of the chat with the given @p chatId. */
    [[nodiscard]] QString title(const QByteArray &chatId) const;

    /*! Returns whether the model is empty (contains no chats). */
    [[nodiscard]] bool isEmpty() const;

    /*! Returns the chat ID for the chat with the given @p chatName, or empty if not found. */
    [[nodiscard]] QByteArray chatIdFromChatName(const QString &chatName) const;

    /*! Returns the associated TextAutoGenerateChatSettings. */
    [[nodiscard]] TextAutoGenerateChatSettings *textAutoGenerateChatSettings() const;
    /*! Sets the TextAutoGenerateChatSettings to @p newTextAutoGenerateChatSettings. */
    void setTextAutoGenerateChatSettings(TextAutoGenerateChatSettings *newTextAutoGenerateChatSettings);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QString title(const TextAutoGenerateChat &chat) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT qint64 dateTime(const TextAutoGenerateChat &chat) const;
    QList<TextAutoGenerateChat> mChats;
    TextAutoGenerateChatSettings *mTextAutoGenerateChatSettings = nullptr;
};
}
