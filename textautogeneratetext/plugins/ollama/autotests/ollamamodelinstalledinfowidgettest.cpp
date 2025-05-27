/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfowidgettest.h"
#include "modelsmanager/ollamamodelinstalledinfowidget.h"
#include <QTest>
QTEST_MAIN(OllamaModelInstalledInfoWidgetTest)

OllamaModelInstalledInfoWidgetTest::OllamaModelInstalledInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInstalledInfoWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelInstalledInfoWidget w;
    // TODO
}

#include "moc_ollamamodelinstalledinfowidgettest.cpp"
