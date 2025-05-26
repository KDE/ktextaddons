/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidgettest.h"
#include "modelsmanager/ollamamodelinstalledwidget.h"
#include <QTest>
QTEST_MAIN(OllamaModelInstalledWidgetTest)

OllamaModelInstalledWidgetTest::OllamaModelInstalledWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInstalledWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelInstalledWidget w;
    // TODO
}

#include "moc_ollamamodelinstalledwidgettest.cpp"
