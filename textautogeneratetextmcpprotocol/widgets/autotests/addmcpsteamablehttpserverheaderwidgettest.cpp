/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpsteamablehttpserverheaderwidgettest.h"
#include "server/addmcpsteamablehttpserverheaderwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(AddMcpSteamableHttpServerHeaderWidgetTest)
using namespace Qt::Literals::StringLiterals;
AddMcpSteamableHttpServerHeaderWidgetTest::AddMcpSteamableHttpServerHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpSteamableHttpServerHeaderWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpSteamableHttpServerHeaderWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
    // TODO
}
#include "moc_addmcpsteamablehttpserverheaderwidgettest.cpp"
