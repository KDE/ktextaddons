/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QSqlDatabase>
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
        PendingTypedInfo,
    };

    explicit TextAutoGenerateLocalDatabaseAbstract(const QString &basePath, DatabaseType type);
    virtual ~TextAutoGenerateLocalDatabaseAbstract();

    [[nodiscard]] QString dbFileName(const QString &id) const;

    // Only for test!
    [[nodiscard]] QString schemaDatabaseStr() const;

protected:
    [[nodiscard]] virtual QString schemaDataBase() const;
    [[nodiscard]] QString databaseName() const;
    [[nodiscard]] bool initializeDataBase(const QString &chatId, QSqlDatabase &db);
    [[nodiscard]] bool checkDataBase(const QString &id, QSqlDatabase &db);
    const QString mBasePath;
    const DatabaseType mDatabaseType = DatabaseType::Unknown;
    [[nodiscard]] QString generateDbName(const QString &id) const;
};

}
