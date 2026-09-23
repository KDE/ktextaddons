/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocalprojectsdatabasetest.h"

#include "core/localdatabase/textautogeneratelocalprojectsdatabase.h"
#include <QSqlRecord>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateLocalProjectsDatabaseTest)

enum class ProjectsFields {
    ProjectId,
    Json,
}; // in the same order as the table

static TextAutoGenerateText::TextAutoGenerateProject createProject(const QByteArray &identifier, const QString &name, const QString &iconName = {})
{
    TextAutoGenerateText::TextAutoGenerateProject project;
    project.setIdentifier(identifier);
    project.setName(name);
    project.setIconName(iconName);
    return project;
}

TextAutoGenerateLocalProjectsDatabaseTest::TextAutoGenerateLocalProjectsDatabaseTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalProjectsDatabaseTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Clean up after previous runs
    TextAutoGenerateText::TextAutoGenerateLocalProjectsDatabase projectsDatabase;
    QFile::remove(projectsDatabase.dbFileName({}));
}

void TextAutoGenerateLocalProjectsDatabaseTest::shouldDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateLocalProjectsDatabase projectsDatabase;
    QCOMPARE(projectsDatabase.schemaDatabaseStr(), u"CREATE TABLE PROJECTS (projectId TEXT PRIMARY KEY NOT NULL, json TEXT)"_s);
}

void TextAutoGenerateLocalProjectsDatabaseTest::shouldVerifyDbFileName()
{
    TextAutoGenerateText::TextAutoGenerateLocalProjectsDatabase projectsDatabase;
    QCOMPARE(projectsDatabase.dbFileName({}),
             QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + u"/ai-database/projects/projects.sqlite"_s);
}

void TextAutoGenerateLocalProjectsDatabaseTest::shouldStoreProjects()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalProjectsDatabase projectsDatabase;

    const auto project1 = createProject("project1", u"name-project1"_s, u"test1"_s);
    projectsDatabase.insertOrUpdateProject(project1);

    const auto project2 = createProject("project2", u"name-project2"_s);
    projectsDatabase.insertOrUpdateProject(project2);

    // WHEN
    auto tableModel = projectsDatabase.createProjectsModel();

    // THEN
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
    const QSqlRecord record0 = tableModel->record(0);
    QCOMPARE(record0.value(int(ProjectsFields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateProject::serialize(project1, false));

    const QSqlRecord record1 = tableModel->record(1);
    QCOMPARE(record1.value(int(ProjectsFields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateProject::serialize(project2, false));
}

void TextAutoGenerateLocalProjectsDatabaseTest::shouldLoadProjects() // this test depends on shouldStoreProjects()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalProjectsDatabase projectsDatabase;

    // WHEN
    const QList<TextAutoGenerateText::TextAutoGenerateProject> projects = projectsDatabase.loadProjects();

    // THEN
    QCOMPARE(projects.count(), 2);
    QCOMPARE(projects.at(0), createProject("project1", u"name-project1"_s, u"test1"_s));
    QCOMPARE(projects.at(1), createProject("project2", u"name-project2"_s));
    QVERIFY(projects.at(1).iconName().isEmpty());
}

void TextAutoGenerateLocalProjectsDatabaseTest::shouldDeleteProjects() // this test depends on shouldStoreProjects()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalProjectsDatabase projectsDatabase;

    // WHEN
    projectsDatabase.deleteProject("project1");

    // THEN
    auto tableModel = projectsDatabase.createProjectsModel();
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 1);
}
#include "moc_textautogeneratelocalprojectsdatabasetest.cpp"
