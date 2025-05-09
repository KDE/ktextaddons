/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseabstract.h"

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
