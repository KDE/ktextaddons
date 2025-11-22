/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseabstract.h"
using namespace Qt::Literals::StringLiterals;

#include "textautogeneratetextcore_database_debug.h"

#include <QDir>
#include <QSqlError>
#include <QSqlQuery>

using namespace TextAutoGenerateText;
TextAutoGenerateLocalDatabaseAbstract::TextAutoGenerateLocalDatabaseAbstract(const QString &basePath, DatabaseType type)
    : mBasePath(basePath)
    , mDatabaseType(type)
{
}

TextAutoGenerateLocalDatabaseAbstract::~TextAutoGenerateLocalDatabaseAbstract() = default;

QString TextAutoGenerateLocalDatabaseAbstract::dbFileName(const QString &id) const
{
    const QString identifier = id.isEmpty() ? databaseName() : id;
    const QString dirPath = mBasePath;
    return dirPath + identifier + u".sqlite"_s;
}

QString TextAutoGenerateLocalDatabaseAbstract::schemaDatabaseStr() const
{
    return schemaDataBase();
}

QString TextAutoGenerateLocalDatabaseAbstract::schemaDataBase() const
{
    Q_ASSERT(false);
    return {};
}

QString TextAutoGenerateLocalDatabaseAbstract::databaseName() const
{
    QString prefix;
    switch (mDatabaseType) {
    case DatabaseType::Unknown:
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Unknown data base it's a bug";
        break;
    case DatabaseType::Chats:
        prefix = u"chats"_s;
        break;
    case DatabaseType::Messages:
        prefix = u"messages"_s;
        break;
    case DatabaseType::PendingTypedInfo:
        prefix = u"pendingtypedinfo-"_s;
        break;
    }
    return prefix;
}

bool TextAutoGenerateLocalDatabaseAbstract::checkDataBase(const QString &id, QSqlDatabase &db)
{
    const QString dbName = generateDbName(id);
    db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG)
            << "The assumption was wrong, deleteMessage was called before addMessage, in account database file " << dbName;
        return false;
    }
    Q_ASSERT(db.isOpen());
    return true;
}

QString TextAutoGenerateLocalDatabaseAbstract::generateDbName(const QString &id) const
{
    return id.isEmpty() ? databaseName() : (databaseName() + QLatin1String("-") + id);
}

bool TextAutoGenerateLocalDatabaseAbstract::initializeDataBase(const QString &id, QSqlDatabase &db)
{
    const QString dbName = generateDbName(id);
    db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase(u"QSQLITE"_s, dbName);
        const QString dirPath = mBasePath;
        if (!QDir().mkpath(dirPath)) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't create" << dirPath;
            return false;
        }
        const QString fileName = dbFileName(id);
        const bool newDb = QFileInfo::exists(fileName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't create" << db.databaseName();
            return false;
        }
        QSqlQuery query(db);
        if (!newDb) {
            query.exec(schemaDataBase());
            if (query.lastError().isValid()) {
                qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't create table LOGS in" << db.databaseName() << ":" << db.lastError();
                return false;
            }
        }
        // Using the write-ahead log and sync = NORMAL for faster writes
        // (idea taken from kactivities-stat)
        query.exec(u"PRAGMA synchronous = 1"_s);
        // use the write-ahead log (requires sqlite > 3.7.0)
        query.exec(u"PRAGMA journal_mode = WAL"_s);
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    return true;
}
