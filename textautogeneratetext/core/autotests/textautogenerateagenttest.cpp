/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateagenttest.h"
#include "core/prompts/textautogenerateagent.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAgentTest)

TextAutoGenerateAgentTest::TextAutoGenerateAgentTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAgentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAgent agent;
    QVERIFY(agent.description().isEmpty());
    QVERIFY(agent.name().isEmpty());
}

#include "moc_textautogenerateagenttest.cpp"
