/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "core/textautogeneratemessage.h"
#include "textautogeneratelocaldatabaseabstract.h"

#include <QSqlTableModel>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalMessagesDatabase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalMessagesDatabase();
    ~TextAutoGenerateLocalMessagesDatabase() override;

    void deleteMessage(const QString &chatIdentifier, const QString &messageId);
    void addMessage(const QString &chatIdentifier, const TextAutoGenerateMessage &m);

    [[nodiscard]] std::unique_ptr<QSqlTableModel> createMessageModel(const QString &chatIdentifier) const;

    [[nodiscard]] QList<TextAutoGenerateMessage> loadMessages(const QString &chatIdentifier) const;

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateMessage convertJsonToMessage(const QString &json) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT static QString generateQueryStr();
};
};
