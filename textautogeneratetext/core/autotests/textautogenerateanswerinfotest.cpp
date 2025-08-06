/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateanswerinfotest.h"
#include "core/textautogenerateanswerinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAnswerInfoTest)

TextAutoGenerateAnswerInfoTest::TextAutoGenerateAnswerInfoTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAnswerInfoTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAnswerInfo info;
    QVERIFY(info.engineName().isEmpty());
    QVERIFY(info.instanceName().isEmpty());
    QVERIFY(info.modelName().isEmpty());
    QVERIFY(!info.isValid());
}

#include "moc_textautogenerateanswerinfotest.cpp"
