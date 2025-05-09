/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocalchatsdatabase.h"
#include "textautogeneratelocaldatabaseutils.h"

using namespace TextAutoGenerateText;
TextAutoGenerateLocalChatsDatabase::TextAutoGenerateLocalChatsDatabase()
    : TextAutoGenerateLocalDatabaseAbstract(TextAutoGenerateLocalDatabaseUtils::localChatsDatabasePath(),
                                            TextAutoGenerateLocalChatsDatabase::DatabaseType::Chats)
{
}

TextAutoGenerateLocalChatsDatabase::~TextAutoGenerateLocalChatsDatabase() = default;
