/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocalprojectsdatabase.h"

#include "textautogeneratelocaldatabaseutils.h"
#include "textautogeneratetextcore_database_debug.h"
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using namespace Qt::Literals::StringLiterals;
static const char s_schemaProjectsDataBase[] = "CREATE TABLE PROJECTS (projectId TEXT PRIMARY KEY NOT NULL, json TEXT)";
enum class ProjectsFields {
    ProjectId,
    Json,
}; // in the same order as the table

using namespace TextAutoGenerateText;
TextAutoGenerateLocalProjectsDatabase::TextAutoGenerateLocalProjectsDatabase()
    : TextAutoGenerateLocalDatabaseAbstract(TextAutoGenerateLocalDatabaseUtils::localProjectsDatabasePath(),
                                            TextAutoGenerateLocalProjectsDatabase::DatabaseType::Projects)
{
}

TextAutoGenerateLocalProjectsDatabase::~TextAutoGenerateLocalProjectsDatabase() = default;

std::unique_ptr<QSqlTableModel> TextAutoGenerateLocalProjectsDatabase::createProjectsModel() const
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
    model->setTable(u"PROJECTS"_s);
    model->select();
    return model;
}

QString TextAutoGenerateLocalProjectsDatabase::schemaDataBase() const
{
    return QString::fromLatin1(s_schemaProjectsDataBase);
}

void TextAutoGenerateLocalProjectsDatabase::insertOrUpdateProject(const TextAutoGenerateProject &project)
{
    if (project.identifier().isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't store a project without identifier" << project;
        return;
    }
    QSqlDatabase db;
    if (initializeDataBase(QString(), db)) {
        QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::insertReplaceProject(), db);
        query.addBindValue(QString::fromLatin1(project.identifier()));
        query.addBindValue(TextAutoGenerateProject::serialize(project, false)); // TODO use binary ?
        if (!query.exec()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't insert-or-replace in PROJECTS table" << db.databaseName() << query.lastError();
        }
    }
}

QList<TextAutoGenerateProject> TextAutoGenerateLocalProjectsDatabase::loadProjects() const
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
    const QString query = TextAutoGenerateLocalProjectsDatabase::generateQueryStr();
    QSqlQuery resultQuery(db);
    if (!resultQuery.prepare(query)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << " Invalid query" << query << " resultQuery " << resultQuery.lastError().text();
        return {};
    }
    if (!resultQuery.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << " Impossible to execute query: " << resultQuery.lastError() << " query: " << query;
        return {};
    }

    QList<TextAutoGenerateProject> listProjects;
    while (resultQuery.next()) {
        const QString json = resultQuery.value(u"json"_s).toString();
        listProjects.append(convertJsonToProject(json));
    }
    return listProjects;
}

TextAutoGenerateProject TextAutoGenerateLocalProjectsDatabase::convertJsonToProject(const QString &json) const
{
    const QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    const TextAutoGenerateProject project = TextAutoGenerateProject::deserialize(doc.object());
    return project;
}

QString TextAutoGenerateLocalProjectsDatabase::generateQueryStr()
{
    const QString query = u"SELECT * FROM PROJECTS"_s;
    return query;
}

void TextAutoGenerateLocalProjectsDatabase::deleteProject(const QByteArray &projectId)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "deleteProject" << projectId;
    QSqlDatabase db;
    if (!checkDataBase(QString(), db)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Problem when check checkDataBase" << projectId;
        return;
    }
    QSqlQuery query(TextAutoGenerateLocalDatabaseUtils::deleteProject(), db);
    query.addBindValue(QString::fromLatin1(projectId));
    if (!query.exec()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Couldn't delete in PROJECTS table" << db.databaseName() << query.lastError();
    }
}
