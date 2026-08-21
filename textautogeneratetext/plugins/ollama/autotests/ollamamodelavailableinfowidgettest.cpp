/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfowidgettest.h"
#include "modelsmanager/ollamamodelavailableinfowidget.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(OllamaModelAvailableInfoWidgetTest)

OllamaModelAvailableInfoWidgetTest::OllamaModelAvailableInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void OllamaModelAvailableInfoWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelAvailableInfoWidget w(nullptr);
    // TODO
}

#include "moc_ollamamodelavailableinfowidgettest.cpp"
