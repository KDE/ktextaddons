/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratelocaldatabaseabstract.h"
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

protected:
    [[nodiscard]] QString schemaDataBase() const override;
};
};
