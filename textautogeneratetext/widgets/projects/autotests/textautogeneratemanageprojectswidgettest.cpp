/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanageprojectswidgettest.h"
#include "widgets/projects/textautogeneratemanageprojectswidget.h"
#include <QHBoxLayout>
#include <QListView>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateManageProjectsWidgetTest)
using namespace Qt::Literals::StringLiterals;
namespace
{
TextAutoGenerateText::TextAutoGenerateProject createProject(const QByteArray &identifier, const QString &name, const QColor &color)
{
    TextAutoGenerateText::TextAutoGenerateProject project;
    project.setIdentifier(identifier);
    project.setName(name);
    project.setColor(color);
    return project;
}
}
TextAutoGenerateManageProjectsWidgetTest::TextAutoGenerateManageProjectsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateManageProjectsWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateManageProjectsWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto buttonLayout = w.findChild<QVBoxLayout *>(u"buttonLayout"_s);
    QVERIFY(buttonLayout);
    QCOMPARE(buttonLayout->contentsMargins(), QMargins{});

    auto mProjectsListView = w.findChild<QListView *>(u"mProjectsListView"_s);
    QVERIFY(mProjectsListView);
    QVERIFY(mProjectsListView->model());
    QCOMPARE(mProjectsListView->model()->rowCount(), 0);

    auto mAddButton = w.findChild<QToolButton *>(u"mAddButton"_s);
    QVERIFY(mAddButton);
    QVERIFY(mAddButton->isEnabled());
    QVERIFY(!mAddButton->toolTip().isEmpty());

    auto mModifyButton = w.findChild<QToolButton *>(u"mModifyButton"_s);
    QVERIFY(mModifyButton);
    QVERIFY(!mModifyButton->isEnabled());
    QVERIFY(!mModifyButton->toolTip().isEmpty());

    auto mRemoveButton = w.findChild<QToolButton *>(u"mRemoveButton"_s);
    QVERIFY(mRemoveButton);
    QVERIFY(!mRemoveButton->isEnabled());
    QVERIFY(!mRemoveButton->toolTip().isEmpty());

    QVERIFY(w.projects().isEmpty());
}

void TextAutoGenerateManageProjectsWidgetTest::shouldStoreProjects()
{
    TextAutoGenerateText::TextAutoGenerateManageProjectsWidget w;
    const QList<TextAutoGenerateText::TextAutoGenerateProject> projects{createProject("project1", u"name-project1"_s, QColor(Qt::red)),
                                                                        createProject("project2", u"name-project2"_s, QColor(Qt::blue))};
    w.setProjects(projects);

    auto mProjectsListView = w.findChild<QListView *>(u"mProjectsListView"_s);
    QVERIFY(mProjectsListView);
    QCOMPARE(mProjectsListView->model()->rowCount(), 2);
    QCOMPARE(w.projects(), projects);
}

void TextAutoGenerateManageProjectsWidgetTest::shouldEnableButtonsWhenSelectingProject()
{
    TextAutoGenerateText::TextAutoGenerateManageProjectsWidget w;
    w.setProjects({createProject("project1", u"name-project1"_s, QColor(Qt::red))});

    auto mProjectsListView = w.findChild<QListView *>(u"mProjectsListView"_s);
    QVERIFY(mProjectsListView);
    auto mModifyButton = w.findChild<QToolButton *>(u"mModifyButton"_s);
    QVERIFY(mModifyButton);
    auto mRemoveButton = w.findChild<QToolButton *>(u"mRemoveButton"_s);
    QVERIFY(mRemoveButton);
    QVERIFY(!mModifyButton->isEnabled());
    QVERIFY(!mRemoveButton->isEnabled());

    // WHEN
    mProjectsListView->setCurrentIndex(mProjectsListView->model()->index(0, 0));

    // THEN
    QVERIFY(mModifyButton->isEnabled());
    QVERIFY(mRemoveButton->isEnabled());

    // WHEN the model is reset, the selection is gone again.
    w.setProjects({});

    // THEN
    QVERIFY(!mModifyButton->isEnabled());
    QVERIFY(!mRemoveButton->isEnabled());
}
#include "moc_textautogeneratemanageprojectswidgettest.cpp"
