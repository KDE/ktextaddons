/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddmcpserverwidgettest.h"
#include "widgets/mcpserver/textautogenerateaddmcpserverwidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateAddMcpServerWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAddMcpServerWidgetTest::TextAutoGenerateAddMcpServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAddMcpServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAddMcpServerWidget w;
    // TODO
}
#include "moc_textautogenerateaddmcpserverwidgettest.cpp"
