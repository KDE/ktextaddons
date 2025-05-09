/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseutils.h"

#include <QStandardPaths>

using namespace TextAutoGenerateText;
QString TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QStringLiteral("/database/");
}

QString TextAutoGenerateLocalDatabaseUtils::localMessagesDatabasePath()
{
    return TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
        + TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath::Messages);
}

QString TextAutoGenerateLocalDatabaseUtils::localChatsDatabasePath()
{
    return TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
        + TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath::Chats);
}

QString TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath pathType)
{
    switch (pathType) {
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::Messages:
        return QStringLiteral("messages/");
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::Chats:
        return QStringLiteral("chats/");
    }
    Q_UNREACHABLE();
    return {};
}

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceChat()
{
    return QStringLiteral("INSERT OR REPLACE INTO CHATS VALUES (?, ?)");
}

QString TextAutoGenerateLocalDatabaseUtils::deleteChat()
{
    return QStringLiteral("DELETE FROM CHATS WHERE chatId = ?");
}

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceMessage()
{
    return QStringLiteral("INSERT OR REPLACE INTO MESSAGES VALUES (?, ?)");
}

QString TextAutoGenerateLocalDatabaseUtils::deleteMessage()
{
    return QStringLiteral("DELETE FROM MESSAGES WHERE messageId = ?");
}
