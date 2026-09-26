/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QSqlTableModel>
#include <TextAutoGenerateText/TextAutoGenerateLocalDatabaseAbstract>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateLocalMessagesDatabase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalMessagesDatabase();
    ~TextAutoGenerateLocalMessagesDatabase() override;

    void deleteMessage(const QByteArray &chatIdentifier, const QString &messageId);
    void insertOrReplaceMessage(const QByteArray &chatIdentifier, const TextAutoGenerateMessage &m);

    [[nodiscard]] std::unique_ptr<QSqlTableModel> createMessageModel(const QString &chatIdentifier) const;

    [[nodiscard]] QList<TextAutoGenerateMessage> loadMessages(const QString &chatIdentifier) const;

    // Returns -1 when the chat has no database or no message. Doesn't create the database.
    [[nodiscard]] qint64 lastMessageDateTime(const QString &chatIdentifier) const;

    [[nodiscard]] QList<TextAutoGenerateSearchMessage> searchMessages(const QString &chatIdentifier, const QString &searchText) const;

    void deleteDatabase(const QByteArray &chatIdentifier);

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateMessage convertJsonToMessage(const QString &json) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT static QString generateQueryStr();
};
}
