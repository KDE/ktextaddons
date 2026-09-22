/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetagsmodeltest.h"
#include "core/models/textautogeneratetagsmodel.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTagsModelTest)
using namespace Qt::Literals::StringLiterals;

static TextAutoGenerateText::TextAutoGenerateTag createTag(const QByteArray &identifier, const QString &name, const QColor &color = {})
{
    TextAutoGenerateText::TextAutoGenerateTag tag;
    tag.setIdentifier(identifier);
    tag.setName(name);
    tag.setColor(color);
    return tag;
}

TextAutoGenerateTagsModelTest::TextAutoGenerateTagsModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTagsModelTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTagsModel model;
    QVERIFY(model.tags().isEmpty());
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTagsModelTest::shouldAddTag()
{
    TextAutoGenerateText::TextAutoGenerateTagsModel model;
    model.addTag(createTag("foo"_ba, u"bla"_s, Qt::red));
    QCOMPARE(model.rowCount(), 1);

    const QModelIndex idx = model.index(0, 0);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTagsModel::Name).toString(), u"bla"_s);
    QCOMPARE(idx.data(Qt::DisplayRole).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTagsModel::Identifier).toByteArray(), "foo"_ba);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateTagsModel::Color).value<QColor>(), QColor(Qt::red));
    QCOMPARE(idx.data(Qt::DecorationRole).value<QColor>(), QColor(Qt::red));

    // No color set => invalid QVariant, so the view keeps its palette instead of painting black.
    model.addTag(createTag("foo1"_ba, u"bla1"_s));
    QCOMPARE(model.rowCount(), 2);
    const QModelIndex idx2 = model.index(1, 0);
    QCOMPARE(idx2.data(TextAutoGenerateText::TextAutoGenerateTagsModel::Name).toString(), u"bla1"_s);
    QVERIFY(!idx2.data(TextAutoGenerateText::TextAutoGenerateTagsModel::Color).isValid());
    QVERIFY(!idx2.data(Qt::DecorationRole).isValid());
}

void TextAutoGenerateTagsModelTest::shouldRemoveTag()
{
    TextAutoGenerateText::TextAutoGenerateTagsModel model;
    model.setTags({createTag("foo"_ba, u"bla"_s), createTag("foo1"_ba, u"bla1"_s)});
    QCOMPARE(model.rowCount(), 2);

    // Unknown identifier => nothing removed
    model.removeTag("unknown"_ba);
    QCOMPARE(model.rowCount(), 2);

    // Empty identifier => nothing removed
    model.removeTag({});
    QCOMPARE(model.rowCount(), 2);

    model.removeTag("foo"_ba);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.tags().at(0).identifier(), "foo1"_ba);
}

void TextAutoGenerateTagsModelTest::shouldUpdateTag()
{
    TextAutoGenerateText::TextAutoGenerateTagsModel model;
    model.setTags({createTag("foo"_ba, u"bla"_s), createTag("foo1"_ba, u"bla1"_s)});

    const QSignalSpy dataChangedSpy(&model, &TextAutoGenerateText::TextAutoGenerateTagsModel::dataChanged);
    model.updateTag(createTag("foo1"_ba, u"newname"_s, Qt::blue));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toModelIndex(), model.index(1, 0));
    QCOMPARE(model.tags().at(1).name(), u"newname"_s);
    QCOMPARE(model.tags().at(1).color(), QColor(Qt::blue));
    // Other tag untouched
    QCOMPARE(model.tags().at(0).name(), u"bla"_s);

    // Unknown identifier => nothing changed
    model.updateTag(createTag("unknown"_ba, u"foobla"_s));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
}

void TextAutoGenerateTagsModelTest::shouldClearTags()
{
    TextAutoGenerateText::TextAutoGenerateTagsModel model;
    model.clear();
    QCOMPARE(model.rowCount(), 0);

    model.setTags({createTag("foo"_ba, u"bla"_s)});
    QCOMPARE(model.rowCount(), 1);
    model.clear();
    QVERIFY(model.tags().isEmpty());
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateTagsModelTest::shouldReturnColors()
{
    TextAutoGenerateText::TextAutoGenerateTagsModel model;
    model.setTags({createTag("foo"_ba, u"bla"_s, Qt::red), createTag("foo1"_ba, u"bla1"_s, Qt::blue), createTag("foo2"_ba, u"bla2"_s)});
    QCOMPARE(model.colorFromIdentifier("foo"_ba), Qt::red);
    QCOMPARE(model.colorFromIdentifier("foo1"_ba), Qt::blue);
    QCOMPARE(model.colorFromIdentifier("foo2"_ba), QColor());

    QCOMPARE(model.colors({"foo"_ba, "foo1"}), QList<QColor>() << Qt::red << Qt::blue);
    QCOMPARE(model.colors({"unknown"_ba, "foo1"}), QList<QColor>() << QColor() << Qt::blue);
}

#include "moc_textautogeneratetagsmodeltest.cpp"
