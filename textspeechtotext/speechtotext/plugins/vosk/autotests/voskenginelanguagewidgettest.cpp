/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskenginelanguagewidgettest.h"
#include "voskenginelanguagewidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(VoskEngineLanguageWidgetTest)
VoskEngineLanguageWidgetTest::VoskEngineLanguageWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void VoskEngineLanguageWidgetTest::shouldHaveDefaultValues()
{
    VoskEngineLanguageWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    // TODO
}

#include "moc_voskenginelanguagewidgettest.cpp"
