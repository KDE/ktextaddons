/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "bergamotenginelanguagewidgettest.h"
#include "bergamotenginelanguagewidget.h"
#include <QTest>
QTEST_MAIN(BergamotEngineLanguageWidgetTest)
BergamotEngineLanguageWidgetTest::BergamotEngineLanguageWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineLanguageWidgetTest::shouldHaveDefaultValues()
{
    BergamotEngineLanguageWidget w;

    // TODO
}
