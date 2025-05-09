/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseutils.h"

#include <QStandardPaths>

using namespace TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils;
QString TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QStringLiteral("/database/");
}

QString TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::localMessagesDatabasePath()
{
    return TextAutoGenerateLocalDatabaseUtils::localDatabasePath()
        + TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath::Messages);
}

QString TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath pathType)
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
