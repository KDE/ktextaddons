/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateprojectsmodeltest.h"
#include "core/models/textautogenerateprojectsmodel.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateProjectsModelTest)
using namespace Qt::Literals::StringLiterals;

static TextAutoGenerateText::TextAutoGenerateProject createProject(const QByteArray &identifier, const QString &name, const QColor &color = {})
{
    TextAutoGenerateText::TextAutoGenerateProject project;
    project.setIdentifier(identifier);
    project.setName(name);
    project.setColor(color);
    return project;
}

TextAutoGenerateProjectsModelTest::TextAutoGenerateProjectsModelTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateProjectsModelTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateProjectsModel model;
    QVERIFY(model.projects().isEmpty());
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateProjectsModelTest::shouldAddProject()
{
    TextAutoGenerateText::TextAutoGenerateProjectsModel model;
    model.addProject(createProject("foo"_ba, u"bla"_s, Qt::red));
    QCOMPARE(model.rowCount(), 1);

    const QModelIndex idx = model.index(0, 0);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateProjectsModel::Name).toString(), u"bla"_s);
    QCOMPARE(idx.data(Qt::DisplayRole).toString(), u"bla"_s);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateProjectsModel::Identifier).toByteArray(), "foo"_ba);
    QCOMPARE(idx.data(TextAutoGenerateText::TextAutoGenerateProjectsModel::Color).value<QColor>(), QColor(Qt::red));
    QCOMPARE(idx.data(Qt::DecorationRole).value<QColor>(), QColor(Qt::red));

    // No color set => invalid QVariant, so the view keeps its palette instead of painting black.
    model.addProject(createProject("foo1"_ba, u"bla1"_s));
    QCOMPARE(model.rowCount(), 2);
    const QModelIndex idx2 = model.index(1, 0);
    QCOMPARE(idx2.data(TextAutoGenerateText::TextAutoGenerateProjectsModel::Name).toString(), u"bla1"_s);
    QVERIFY(!idx2.data(TextAutoGenerateText::TextAutoGenerateProjectsModel::Color).isValid());
    QVERIFY(!idx2.data(Qt::DecorationRole).isValid());
}

void TextAutoGenerateProjectsModelTest::shouldRemoveProject()
{
    TextAutoGenerateText::TextAutoGenerateProjectsModel model;
    model.setProjects({createProject("foo"_ba, u"bla"_s), createProject("foo1"_ba, u"bla1"_s)});
    QCOMPARE(model.rowCount(), 2);

    // Unknown identifier => nothing removed
    model.removeProject("unknown"_ba);
    QCOMPARE(model.rowCount(), 2);

    // Empty identifier => nothing removed
    model.removeProject({});
    QCOMPARE(model.rowCount(), 2);

    model.removeProject("foo"_ba);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.projects().at(0).identifier(), "foo1"_ba);
}

void TextAutoGenerateProjectsModelTest::shouldUpdateProject()
{
    TextAutoGenerateText::TextAutoGenerateProjectsModel model;
    model.setProjects({createProject("foo"_ba, u"bla"_s), createProject("foo1"_ba, u"bla1"_s)});

    const QSignalSpy dataChangedSpy(&model, &TextAutoGenerateText::TextAutoGenerateProjectsModel::dataChanged);
    model.updateProject(createProject("foo1"_ba, u"newname"_s, Qt::blue));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(dataChangedSpy.at(0).at(0).toModelIndex(), model.index(1, 0));
    QCOMPARE(model.projects().at(1).name(), u"newname"_s);
    QCOMPARE(model.projects().at(1).color(), QColor(Qt::blue));
    // Other project untouched
    QCOMPARE(model.projects().at(0).name(), u"bla"_s);

    // Unknown identifier => nothing changed
    model.updateProject(createProject("unknown"_ba, u"foobla"_s));
    QCOMPARE(dataChangedSpy.count(), 1);
    QCOMPARE(model.rowCount(), 2);
}

void TextAutoGenerateProjectsModelTest::shouldClearProjects()
{
    TextAutoGenerateText::TextAutoGenerateProjectsModel model;
    model.clear();
    QCOMPARE(model.rowCount(), 0);

    model.setProjects({createProject("foo"_ba, u"bla"_s)});
    QCOMPARE(model.rowCount(), 1);
    model.clear();
    QVERIFY(model.projects().isEmpty());
    QCOMPARE(model.rowCount(), 0);
}

void TextAutoGenerateProjectsModelTest::shouldReturnNameAndColor()
{
    TextAutoGenerateText::TextAutoGenerateProjectsModel model;
    model.setProjects({createProject("foo"_ba, u"bla"_s, Qt::red), createProject("foo1"_ba, u"bla1"_s)});
    QCOMPARE(model.nameFromIdentifier("foo"_ba), u"bla"_s);
    QCOMPARE(model.nameFromIdentifier("foo1"_ba), u"bla1"_s);
    QVERIFY(model.nameFromIdentifier("unknown"_ba).isEmpty());
    QVERIFY(model.nameFromIdentifier({}).isEmpty());

    QCOMPARE(model.colorFromIdentifier("foo"_ba), QColor(Qt::red));
    QCOMPARE(model.colorFromIdentifier("foo1"_ba), QColor());
    QCOMPARE(model.colorFromIdentifier("unknown"_ba), QColor());
}

#include "moc_textautogenerateprojectsmodeltest.cpp"
