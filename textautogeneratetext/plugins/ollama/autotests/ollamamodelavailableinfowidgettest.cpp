/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfowidgettest.h"
#include "modelsmanager/ollamamodelavailableinfowidget.h"
#include <QTest>
QTEST_MAIN(OllamaModelAvailableInfoWidgetTest)

OllamaModelAvailableInfoWidgetTest::OllamaModelAvailableInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelAvailableInfoWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelAvailableInfoWidget w(nullptr);
    // TODO
}

#include "moc_ollamamodelavailableinfowidgettest.cpp"
