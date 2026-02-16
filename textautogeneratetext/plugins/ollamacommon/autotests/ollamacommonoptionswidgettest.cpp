/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonoptionswidgettest.h"
#include "ollamacommonoptionswidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaCommonOptionsWidgetTest)
using namespace Qt::Literals::StringLiterals;
OllamaCommonOptionsWidgetTest::OllamaCommonOptionsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCommonOptionsWidgetTest::shouldHaveDefaultValues()
{
    const OllamaCommonOptionsWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
    // TODO
}
