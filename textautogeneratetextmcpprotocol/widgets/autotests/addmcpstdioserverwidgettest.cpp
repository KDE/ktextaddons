/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstdioserverwidgettest.h"
#include "server/addmcpstdioserverwidget.h"
#include <QTest>
QTEST_MAIN(AddMcpStdioServerWidgetTest)

AddMcpStdioServerWidgetTest::AddMcpStdioServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpStdioServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerWidget w;
    // TODO
}
#include "moc_addmcpstdioserverwidgettest.cpp"
