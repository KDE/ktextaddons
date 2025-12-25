/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <TextAutoGenerateText/TextAutoGenerateChat>

#include <QAbstractListModel>
namespace TextAutoGenerateText
{
class TextAutoGenerateChatSettings;
/**
 * @brief The TextAutoGenerateChatsModel class
 * @author Laurent Montel <montel@kde.org>
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

    explicit TextAutoGenerateChatsModel(QObject *parent = nullptr);
    ~TextAutoGenerateChatsModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] TextAutoGenerateChat chat(const QByteArray &chatId) const;

    [[nodiscard]] QList<TextAutoGenerateChat> chats() const;
    void setChats(const QList<TextAutoGenerateChat> &newMessages);

    void addChat(const TextAutoGenerateChat &chat);
    [[nodiscard]] static QString sectionName(TextAutoGenerateChat::SectionHistory sectionId);

    [[nodiscard]] TextAutoGenerateMessagesModel *messagesModel(const QByteArray &chatId) const;

    [[nodiscard]] bool isInitialized(const QByteArray &chatId) const;

    void setInitialized(const QByteArray &chatId, bool state);

    void messagesChanged(const QByteArray &chatId);

    void removeDiscussion(const QByteArray &chatId);

    void changeFavorite(const QByteArray &chatId, bool favorite);

    void archiveDiscussion(const QByteArray &chatId, bool favorite);

    [[nodiscard]] bool chatIsFavorited(const QByteArray &chatId) const;
    [[nodiscard]] bool chatIsArchived(const QByteArray &chatId) const;
    [[nodiscard]] bool chatInProgress(const QByteArray &chatId) const;

    [[nodiscard]] QList<QByteArray> chatsId() const;

    void setChatInProgress(const QByteArray &chatId, bool state);

    [[nodiscard]] QString title(const QByteArray &chatId) const;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] QByteArray chatIdFromChatName(const QString &chatName) const;

    [[nodiscard]] TextAutoGenerateChatSettings *textAutoGenerateChatSettings() const;
    void setTextAutoGenerateChatSettings(TextAutoGenerateChatSettings *newTextAutoGenerateChatSettings);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QString title(const TextAutoGenerateChat &chat) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT qint64 dateTime(const TextAutoGenerateChat &chat) const;
    QList<TextAutoGenerateChat> mChats;
    TextAutoGenerateChatSettings *mTextAutoGenerateChatSettings = nullptr;
};
}
