/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanagertest.h"
#include "core/textautogeneratemanager.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateManagerTest)

TextAutoGenerateManagerTest::TextAutoGenerateManagerTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateManagerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateManager w;
    QVERIFY(w.currentChatId().isEmpty());
    QVERIFY(w.textAutoGenerateChatsModel());
    QVERIFY(!w.showArchived());
    QVERIFY(!w.debug());
}

void TextAutoGenerateManagerTest::shouldIsFavorite()
{
    const TextAutoGenerateText::TextAutoGenerateManager w;
    QVERIFY(!w.chatIsFavorite({}));
}

void TextAutoGenerateManagerTest::shouldSetDebug()
{
    qputenv("TEXTAUTOGENERATE_DEBUGGING", "1");
    const TextAutoGenerateText::TextAutoGenerateManager w;
    QVERIFY(w.debug());
}
#include "moc_textautogeneratemanagertest.cpp"
