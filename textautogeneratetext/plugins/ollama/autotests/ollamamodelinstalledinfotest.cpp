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
    OllamaModelInstalledInfo w;
    QVERIFY(w.model().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.quantizationLevel().isEmpty());
    QVERIFY(w.family().isEmpty());
    QVERIFY(w.parameterSize().isEmpty());
    QVERIFY(w.modifyAt().isEmpty());
}

#include "moc_ollamamodelinstalledinfotest.cpp"
