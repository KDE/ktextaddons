/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfigurecustomizewidgettest.h"
#include "ollamaconfigurecustomizewidget.h"

#include <QFormLayout>
#include <QTest>

QTEST_MAIN(OllamaConfigureCustomizeWidgetTest)
using namespace Qt::Literals::StringLiterals;

OllamaConfigureCustomizeWidgetTest::OllamaConfigureCustomizeWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaConfigureCustomizeWidgetTest::shouldHaveDefaultValues()
{
    const OllamaConfigureCustomizeWidget w;

    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

#include "moc_ollamaconfigurecustomizewidgettest.cpp"
