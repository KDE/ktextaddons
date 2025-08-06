/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessagetest.h"
#include "core/textautogeneratesearchmessage.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateSearchMessageTest)

TextAutoGenerateSearchMessageTest::TextAutoGenerateSearchMessageTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchMessageTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSearchMessage w;
    QVERIFY(w.messageId().isEmpty());
    QVERIFY(w.chatId().isEmpty());
    QVERIFY(w.previewText().isEmpty());
    QCOMPARE(w.dateTime(), -1);
}

#include "moc_textautogeneratesearchmessagetest.cpp"
