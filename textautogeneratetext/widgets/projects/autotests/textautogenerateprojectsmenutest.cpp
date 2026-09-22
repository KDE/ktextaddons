/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprojectsmenutest.h"
#include "widgets/projects/textautogenerateprojectsmenu.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateProjectsMenuTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateProjectsMenuTest::TextAutoGenerateProjectsMenuTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateProjectsMenuTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateProjectsMenu m(nullptr);
    QVERIFY(!m.title().isEmpty());
    QVERIFY(m.chatId().isEmpty());
}

void TextAutoGenerateProjectsMenuTest::shouldShowOnlyManageActionWithoutChatId()
{
    // GIVEN a menu without manager nor chat, THEN it only offers to manage the projects.
    TextAutoGenerateText::TextAutoGenerateProjectsMenu m(nullptr);
    QCOMPARE(m.actions().count(), 1);
    QVERIFY(m.findChild<QAction *>(u"manageProjectsAction"_s));

    // WHEN a chat identifier is assigned but no manager is available
    m.setChatId("chat1");

    // THEN the menu is unchanged, as there is no project to move the chat to.
    QCOMPARE(m.chatId(), "chat1"_ba);
    QCOMPARE(m.actions().count(), 1);
    QVERIFY(m.findChild<QAction *>(u"manageProjectsAction"_s));
    QVERIFY(!m.findChild<QAction *>(u"noProjectAction"_s));
}
#include "moc_textautogenerateprojectsmenutest.cpp"
