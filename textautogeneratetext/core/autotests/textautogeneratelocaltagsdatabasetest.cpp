/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocaltagsdatabasetest.h"

#include "core/localdatabase/textautogeneratelocaltagsdatabase.h"
#include <QSqlRecord>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateLocalTagsDatabaseTest)

enum class TagsFields {
    TagId,
    Json,
}; // in the same order as the table

static TextAutoGenerateText::TextAutoGenerateTag createTag(const QByteArray &identifier, const QString &name, const QColor &color = {})
{
    TextAutoGenerateText::TextAutoGenerateTag tag;
    tag.setIdentifier(identifier);
    tag.setName(name);
    tag.setColor(color);
    return tag;
}

TextAutoGenerateLocalTagsDatabaseTest::TextAutoGenerateLocalTagsDatabaseTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalTagsDatabaseTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Clean up after previous runs
    TextAutoGenerateText::TextAutoGenerateLocalTagsDatabase tagsDatabase;
    QFile::remove(tagsDatabase.dbFileName({}));
}

void TextAutoGenerateLocalTagsDatabaseTest::shouldDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateLocalTagsDatabase tagsDatabase;
    QCOMPARE(tagsDatabase.schemaDatabaseStr(), u"CREATE TABLE TAGS (tagId TEXT PRIMARY KEY NOT NULL, json TEXT)"_s);
}

void TextAutoGenerateLocalTagsDatabaseTest::shouldVerifyDbFileName()
{
    TextAutoGenerateText::TextAutoGenerateLocalTagsDatabase tagsDatabase;
    QCOMPARE(tagsDatabase.dbFileName({}), QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + u"/ai-database/tags/tags.sqlite"_s);
}

void TextAutoGenerateLocalTagsDatabaseTest::shouldStoreTags()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalTagsDatabase tagsDatabase;

    const auto tag1 = createTag("tag1", u"name-tag1"_s, QColor(Qt::red));
    tagsDatabase.insertOrUpdateTag(tag1);

    const auto tag2 = createTag("tag2", u"name-tag2"_s);
    tagsDatabase.insertOrUpdateTag(tag2);

    // WHEN
    auto tableModel = tagsDatabase.createTagsModel();

    // THEN
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
    const QSqlRecord record0 = tableModel->record(0);
    QCOMPARE(record0.value(int(TagsFields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateTag::serialize(tag1, false));

    const QSqlRecord record1 = tableModel->record(1);
    QCOMPARE(record1.value(int(TagsFields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateTag::serialize(tag2, false));
}

void TextAutoGenerateLocalTagsDatabaseTest::shouldLoadTags() // this test depends on shouldStoreTags()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalTagsDatabase tagsDatabase;

    // WHEN
    const QList<TextAutoGenerateText::TextAutoGenerateTag> tags = tagsDatabase.loadTags();

    // THEN
    QCOMPARE(tags.count(), 2);
    QCOMPARE(tags.at(0), createTag("tag1", u"name-tag1"_s, QColor(Qt::red)));
    QCOMPARE(tags.at(1), createTag("tag2", u"name-tag2"_s));
    QVERIFY(!tags.at(1).color().isValid());
}

void TextAutoGenerateLocalTagsDatabaseTest::shouldDeleteTags() // this test depends on shouldStoreTags()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalTagsDatabase tagsDatabase;

    // WHEN
    tagsDatabase.deleteTag("tag1");

    // THEN
    auto tableModel = tagsDatabase.createTagsModel();
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 1);
}
#include "moc_textautogeneratelocaltagsdatabasetest.cpp"
