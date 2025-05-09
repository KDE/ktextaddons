/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratelocaldatabaseabstract.h"

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalChatsDatabase : public TextAutoGenerateText::TextAutoGenerateLocalDatabaseAbstract
{
public:
    TextAutoGenerateLocalChatsDatabase();
    ~TextAutoGenerateLocalChatsDatabase() override;
};
};
