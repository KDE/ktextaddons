/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextreplyinfotest.h"
#include <QTest>
#include <TextAutoGenerateText/TextAutoGenerateTextReplyInfo>
QTEST_GUILESS_MAIN(TextAutoGenerateTextReplyInfoTest)

TextAutoGenerateTextReplyInfoTest::TextAutoGenerateTextReplyInfoTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextReplyInfoTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextReplyInfo info;
    QCOMPARE(info.completionTokens, 0);
    QCOMPARE(info.promptTokens, 0);
    QCOMPARE(info.promptEvalTokenCount, 0);
    QCOMPARE(info.tokenCount, 0);
    QVERIFY(!info.isValid());
    // TODO
}

#include "moc_textautogeneratetextreplyinfotest.cpp"
