/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <TextAutoGenerateText/TextAutoGenerateChat>

#include <QAbstractListModel>
namespace TextAutoGenerateText
{
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
        DateTime,
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

    [[nodiscard]] QList<TextAutoGenerateChat> chats() const;
    void setChats(const QList<TextAutoGenerateChat> &newMessages);

    void addChat(const TextAutoGenerateChat &chat);
    [[nodiscard]] static QString sectionName(SectionHistory sectionId);

    [[nodiscard]] TextAutoGenerateMessagesModel *messagesModel(const QByteArray &chatId) const;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QString title(const TextAutoGenerateChat &chat) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateChatsModel::SectionHistory section(const TextAutoGenerateMessage &m) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateChatsModel::SectionHistory section(const TextAutoGenerateChat &chat) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT qint64 dateTime(const TextAutoGenerateChat &chat) const;
    QList<TextAutoGenerateChat> mChats;
};
}
