/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QSortFilterProxyModel>
#include <QString>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalDatabaseAbstract
{
public:
    enum class DatabaseType {
        Unknown = 0,
        Chats,
        Messages,
    };

    explicit TextAutoGenerateLocalDatabaseAbstract(const QString &basePath, DatabaseType type);
    virtual ~TextAutoGenerateLocalDatabaseAbstract();

    [[nodiscard]] QString dbFileName(const QString &identifier) const;

protected:
    const QString mBasePath;
    const DatabaseType mDatabaseType = DatabaseType::Unknown;
};

}
