/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpsseserverwidgettest.h"
#include "server/addmcpsseserverwidget.h"
#include <QTest>
QTEST_MAIN(AddMcpSseServerWidgetTest)

AddMcpSseServerWidgetTest::AddMcpSseServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpSseServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpSseServerWidget w;
    // TODO
}
