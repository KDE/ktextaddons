/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateprompttest.h"
#include "core/prompts/textautogenerateprompt.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGeneratePromptTest)

TextAutoGeneratePromptTest::TextAutoGeneratePromptTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGeneratePromptTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGeneratePrompt prompt;
    QVERIFY(prompt.name().isEmpty());
    QVERIFY(prompt.text().isEmpty());
}

#include "moc_textautogenerateprompttest.cpp"
