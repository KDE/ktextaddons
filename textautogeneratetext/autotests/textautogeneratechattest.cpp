/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechattest.h"
#include "core/textautogeneratechat.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateChatTest)

TextAutoGenerateChatTest::TextAutoGenerateChatTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateChat w;
    QVERIFY(!w.favorite());
    QVERIFY(!w.archived());
    QVERIFY(w.title().isEmpty());
    QVERIFY(w.identifier().isEmpty());

    // 10/05/2025 => size 72
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateChat), 72);
}

#include "moc_textautogeneratechattest.cpp"
