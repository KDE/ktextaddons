/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaenginewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "../lingvaenginewidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(LingvaEngineWidgetTest)
LingvaEngineWidgetTest::LingvaEngineWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void LingvaEngineWidgetTest::shouldHaveDefaultValues()
{
    LingvaEngineWidget w;
    QVERIFY(w.serverUrl().isEmpty());

    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mServerUrl = w.findChild<QLineEdit *>(u"mServerUrl"_s);
    QVERIFY(mServerUrl);
    QVERIFY(mServerUrl->isClearButtonEnabled());
}

#include "moc_lingvaenginewidgettest.cpp"
