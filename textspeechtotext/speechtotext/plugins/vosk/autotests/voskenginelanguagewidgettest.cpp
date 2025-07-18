/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskenginelanguagewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    // TODO
}

#include "moc_voskenginelanguagewidgettest.cpp"
