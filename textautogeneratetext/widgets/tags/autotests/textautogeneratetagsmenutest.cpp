/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetagsmenutest.h"
#include "widgets/tags/textautogeneratetagsmenu.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateTagsMenuTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTagsMenuTest::TextAutoGenerateTagsMenuTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTagsMenuTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTagsMenu m(nullptr);
    QVERIFY(!m.title().isEmpty());
    QVERIFY(m.chatId().isEmpty());
}

void TextAutoGenerateTagsMenuTest::shouldShowOnlyManageActionWithoutChatId()
{
    // GIVEN a menu without manager nor chat, THEN it only offers to manage the tags.
    TextAutoGenerateText::TextAutoGenerateTagsMenu m(nullptr);
    QCOMPARE(m.actions().count(), 1);
    QVERIFY(m.findChild<QAction *>(u"manageTagsAction"_s));

    // WHEN a chat identifier is assigned but no manager is available
    m.setChatId("chat1");

    // THEN the menu is unchanged, as there is no tag to assign.
    QCOMPARE(m.chatId(), "chat1"_ba);
    QCOMPARE(m.actions().count(), 1);
    QVERIFY(m.findChild<QAction *>(u"manageTagsAction"_s));
}
#include "moc_textautogeneratetagsmenutest.cpp"
