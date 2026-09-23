/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanageprojectsdialogtest.h"
#include "widgets/projects/textautogeneratemanageprojectsdialog.h"
#include "widgets/projects/textautogeneratemanageprojectswidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateManageProjectsDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateManageProjectsDialogTest::TextAutoGenerateManageProjectsDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateManageProjectsDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateManageProjectsDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mManageProjectsWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateManageProjectsWidget *>(u"mManageProjectsWidget"_s);
    QVERIFY(mManageProjectsWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);

    QVERIFY(d.projects().isEmpty());
}

void TextAutoGenerateManageProjectsDialogTest::shouldStoreProjects()
{
    TextAutoGenerateText::TextAutoGenerateManageProjectsDialog d;
    TextAutoGenerateText::TextAutoGenerateProject project;
    project.setIdentifier("project1");
    project.setName(u"name-project1"_s);
    project.setIconName(u"bla2"_s);
    const QList<TextAutoGenerateText::TextAutoGenerateProject> projects{project};
    d.setProjects(projects);
    QCOMPARE(d.projects(), projects);
}
#include "moc_textautogeneratemanageprojectsdialogtest.cpp"
