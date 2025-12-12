/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseutils.h"

#include <QStandardPaths>

using namespace Qt::Literals::StringLiterals;
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
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::RoomPendingTypedInfo:
        return u"roompendingtypedinfo/"_s;
    }
    Q_UNREACHABLE();
    return {};
}

QString TextAutoGenerateLocalDatabaseUtils::localRoomPendingTypedInfoDatabasePath()
{
    return TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
        + TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath::RoomPendingTypedInfo);
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

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceRoomPendingTypedInfo()
{
    return u"INSERT OR REPLACE INTO ROOMPENDINGTYPED VALUES (?, ?)"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::deleteRoomPendingTypedInfo()
{
    return u"DELETE FROM ROOMPENDINGTYPED WHERE roomId = ?"_s;
}
