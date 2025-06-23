/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseutils.h"
using namespace Qt::Literals::StringLiterals;

#include <QStandardPaths>

using namespace TextAutoGenerateText;
QString TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + u"/ai-database/"_s;
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
        return u"messages/"_s;
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::Chats:
        return u"chats/"_s;
    }
    Q_UNREACHABLE();
    return {};
}

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceChat()
{
    return u"INSERT OR REPLACE INTO CHATS VALUES (?, ?)"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::deleteChat()
{
    return u"DELETE FROM CHATS WHERE chatId = ?"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceMessage()
{
    return u"INSERT OR REPLACE INTO MESSAGES VALUES (?, ?, ?)"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::deleteMessage()
{
    return u"DELETE FROM MESSAGES WHERE messageId = ?"_s;
}
