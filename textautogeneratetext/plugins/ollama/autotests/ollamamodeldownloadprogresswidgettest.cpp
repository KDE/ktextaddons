/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadprogresswidgettest.h"
#include "modelsmanager/ollamamodeldownloadprogresswidget.h"
#include <QTest>
QTEST_MAIN(OllamaModelDownloadProgressWidgetTest)

OllamaModelDownloadProgressWidgetTest::OllamaModelDownloadProgressWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadProgressWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadProgressWidget w;
    // TODO
}
