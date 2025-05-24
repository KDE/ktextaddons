/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfowidgettest.h"
#include "modelsmanager/ollamamodelinfowidget.h"
#include <QTest>
QTEST_MAIN(OllamaModelInfoWidgetTest)
OllamaModelInfoWidgetTest::OllamaModelInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInfoWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelInfoWidget w;
    // TODO
}
