/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpservertest.h"
#include "core/textautogeneratetextmcpserver.h"

#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextMcpServerTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextMcpServerTest::TextAutoGenerateTextMcpServerTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextMcpServerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextMcpServer w;
    QVERIFY(w.serverUrl().isEmpty());
    QVERIFY(w.enabled());
}

#include "moc_textautogeneratetextmcpservertest.cpp"
