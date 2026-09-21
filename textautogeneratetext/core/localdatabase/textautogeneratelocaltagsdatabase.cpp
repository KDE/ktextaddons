/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaltagsdatabase.h"

#include "textautogeneratelocaldatabaseutils.h"
#include "textautogeneratetextcore_database_debug.h"
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using namespace Qt::Literals::StringLiterals;
static const char s_schemaTagsDataBase[] = "CREATE TABLE TAGS (tagId TEXT PRIMARY KEY NOT NULL, json TEXT)";
enum class TagsFields {
    TagId,
    Json,
}; // in the same order as the table

using namespace TextAutoGenerateText;
TextAutoGenerateLocalTagsDatabase::TextAutoGenerateLocalTagsDatabase()
    : TextAutoGenerateLocalDatabaseAbstract(TextAutoGenerateLocalDatabaseUtils::localTagsDatabasePath(), TextAutoGenerateLocalTagsDatabase::DatabaseType::Tags)
{
}

TextAutoGenerateLocalTagsDatabase::~TextAutoGenerateLocalTagsDatabase() = default;

std::unique_ptr<QSqlTableModel> TextAutoGenerateLocalTagsDatabase::createTagsModel() const
{
    const QString dbName = generateDbName({});
    QSqlDatabase db = QSqlDatabase::database(dbName);
    if (!db.isValid()) {
        // Open the DB if it exists (don't create a new one)
        const QString fileName = dbFileName({});
        if (!QFileInfo::exists(fileName)) {
            return {};
        }
        db = QSqlDatabase::addDatabase(u"QSQLITE"_s, dbName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't open" << fileName;
            return {};
        }
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    auto model = std::make_unique<QSqlTableModel>(nullptr, db);
    model->setTable(u"TAGS"_s);
    model->select();
    return model;
}

QString TextAutoGenerateLocalTagsDatabase::schemaDataBase() const
{
    return QString::fromLatin1(s_schemaTagsDataBase);
}

void TextAutoGenerateLocalTagsDatabase::insertOrUpdateTag(const TextAutoGenerateTag &tag)
{
    if (tag.identifier().isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't store a tag without identifier" << tag;
        return;
    }
    QSqlDatabase db;
    if (initializeDataBase(QString(), db)) {
        QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::insertReplaceTag(), db);
        query.addBindValue(QString::fromLatin1(tag.identifier()));
        query.addBindValue(TextAutoGenerateTag::serialize(tag, false)); // TODO use binary ?
        if (!query.exec()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in TAGS table" << db.databaseName() << query.lastError();
        }
    }
}

QList<TextAutoGenerateTag> TextAutoGenerateLocalTagsDatabase::loadTags() const
{
    const QString dbName = generateDbName(QString());
    QSqlDatabase db = QSqlDatabase::database(dbName);
    if (!db.isValid() || !db.isOpen()) {
        // Open the DB if it exists (don't create a new one)
        const QString fileName = dbFileName(QString());
        if (!QFileInfo::exists(fileName)) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Filename doesn't exist: " << fileName;
            return {};
        }
        db = QSqlDatabase::addDatabase(u"QSQLITE"_s, dbName);
        db.setDatabaseName(fileName);
        if (!db.open()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't open" << fileName;
            return {};
        }
    }

    Q_ASSERT(db.isValid());
    Q_ASSERT(db.isOpen());
    const QString query = TextAutoGenerateLocalTagsDatabase::generateQueryStr();
    QSqlQuery resultQuery(db);
    if (!resultQuery.prepare(query)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << " Invalid query" << query << " resultQuery " << resultQuery.lastError().text();
        return {};
    }
    if (!resultQuery.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << " Impossible to execute query: " << resultQuery.lastError() << " query: " << query;
        return {};
    }

    QList<TextAutoGenerateTag> listTags;
    while (resultQuery.next()) {
        const QString json = resultQuery.value(u"json"_s).toString();
        listTags.append(convertJsonToTag(json));
    }
    return listTags;
}

TextAutoGenerateTag TextAutoGenerateLocalTagsDatabase::convertJsonToTag(const QString &json) const
{
    const QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    const TextAutoGenerateTag tag = TextAutoGenerateTag::deserialize(doc.object());
    return tag;
}

QString TextAutoGenerateLocalTagsDatabase::generateQueryStr()
{
    const QString query = u"SELECT * FROM TAGS"_s;
    return query;
}

void TextAutoGenerateLocalTagsDatabase::deleteTag(const QByteArray &tagId)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "deleteTag" << tagId;
    QSqlDatabase db;
    if (!checkDataBase(QString(), db)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Problem when check checkDataBase" << tagId;
        return;
    }
    QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::deleteTag(), db);
    query.addBindValue(QString::fromLatin1(tagId));
    if (!query.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't delete in TAGS table" << db.databaseName() << query.lastError();
    }
}
