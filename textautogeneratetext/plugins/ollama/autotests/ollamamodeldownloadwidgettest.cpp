/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadwidgettest.h"
#include "modelsmanager/ollamamodeldownloadwidget.h"
#include <QTest>
QTEST_MAIN(OllamaModelDownloadWidgetTest)

OllamaModelDownloadWidgetTest::OllamaModelDownloadWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadWidget w;
    // TODO
}

#include "moc_ollamamodeldownloadwidgettest.cpp"
