/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

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

QString TextAutoGenerateLocalDatabaseUtils::localTagsDatabasePath()
{
    return TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
        + TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath::Tags);
}

QString TextAutoGenerateLocalDatabaseUtils::localProjectsDatabasePath()
{
    return TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
        + TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath::Projects);
}

QString TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath pathType)
{
    switch (pathType) {
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::Messages:
        return u"messages/"_s;
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::Chats:
        return u"chats/"_s;
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::ChatPendingTypedInfo:
        return u"roompendingtypedinfo/"_s;
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::Tags:
        return u"tags/"_s;
    case TextAutoGenerateLocalDatabaseUtils::DatabasePath::Projects:
        return u"projects/"_s;
    }
    Q_UNREACHABLE();
    return {};
}

QString TextAutoGenerateLocalDatabaseUtils::localChatPendingTypedInfoDatabasePath()
{
    return TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
        + TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath::ChatPendingTypedInfo);
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

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceChatPendingTypedInfo()
{
    return u"INSERT OR REPLACE INTO ROOMPENDINGTYPED VALUES (?, ?)"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::deleteChatPendingTypedInfo()
{
    return u"DELETE FROM ROOMPENDINGTYPED WHERE roomId = ?"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceTag()
{
    return u"INSERT OR REPLACE INTO TAGS VALUES (?, ?)"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::deleteTag()
{
    return u"DELETE FROM TAGS WHERE tagId = ?"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::insertReplaceProject()
{
    return u"INSERT OR REPLACE INTO PROJECTS VALUES (?, ?)"_s;
}

QString TextAutoGenerateLocalDatabaseUtils::deleteProject()
{
    return u"DELETE FROM PROJECTS WHERE projectId = ?"_s;
}
