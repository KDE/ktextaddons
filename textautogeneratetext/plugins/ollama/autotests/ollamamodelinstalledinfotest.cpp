/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfotest.h"
#include "modelsmanager/ollamamodelinstalledinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaModelInstalledInfoTest)

OllamaModelInstalledInfoTest::OllamaModelInstalledInfoTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInstalledInfoTest::shouldHaveDefaultValues()
{
    // TODO
    OllamaModelInstalledInfo w;
}

#include "moc_ollamamodelinstalledinfotest.cpp"
