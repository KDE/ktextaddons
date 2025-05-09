/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratelocaldatabaseabstract.h"
#include "textautogeneratetext_private_export.h"
#include <TextAutoGenerateText/TextAutoGenerateChat>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalChatsDatabase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalChatsDatabase();
    ~TextAutoGenerateLocalChatsDatabase() override;

    void deleteChat(const QString &chatId);
    void insertOrUpdateChat(const TextAutoGenerateChat &chat);

    [[nodiscard]] QList<TextAutoGenerateChat> loadChats() const;

protected:
    [[nodiscard]] QString schemaDataBase() const override;

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT static QString generateQueryStr();
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateChat convertJsonToMessage(const QString &json) const;
};
};
