/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadfromnamedialogtest.h"
#include "modelsmanager/ollamamodeldownloadfromnamedialog.h"
#include "modelsmanager/ollamamodeldownloadfromnamewidget.h"
#include <QTest>
QTEST_MAIN(OllamaModelDownloadFromNameDialogTest)

OllamaModelDownloadFromNameDialogTest::OllamaModelDownloadFromNameDialogTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadFromNameDialogTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadFromNameDialog w;

    // TODO
}

#include "moc_ollamamodeldownloadfromnamedialogtest.cpp"
