/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseabstract.h"
#include "textautogeneratetextcore_database_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateLocalDatabaseAbstract::TextAutoGenerateLocalDatabaseAbstract(const QString &basePath, DatabaseType type)
    : mBasePath(basePath)
    , mDatabaseType(type)
{
}

TextAutoGenerateLocalDatabaseAbstract::~TextAutoGenerateLocalDatabaseAbstract() = default;

QString TextAutoGenerateLocalDatabaseAbstract::dbFileName(const QString &identifier) const
{
    const QString dirPath = mBasePath;
    return dirPath + QLatin1Char('/') + identifier + QStringLiteral(".sqlite");
}

QString TextAutoGenerateLocalDatabaseAbstract::databaseName() const
{
    QString prefix;
    switch (mDatabaseType) {
    case DatabaseType::Unknown:
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Unknown data base it's a bug";
        break;
    case DatabaseType::Chats:
        prefix = QStringLiteral("chats");
        break;
    case DatabaseType::Messages:
        prefix = QStringLiteral("messages");
        break;
    }
    return prefix;
}
