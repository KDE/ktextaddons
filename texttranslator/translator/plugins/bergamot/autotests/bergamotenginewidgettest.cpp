/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginewidgettest.h"
#include "bergamotenginewidget.h"
#include <QTest>
QTEST_MAIN(BergamotEngineWidgetTest)
BergamotEngineWidgetTest::BergamotEngineWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineWidgetTest::shouldHaveDefaultValues()
{
    BergamotEngineWidget w;
    // TODO
}

#include "moc_bergamotenginewidgettest.cpp"
