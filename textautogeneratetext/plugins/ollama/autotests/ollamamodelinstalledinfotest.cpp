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

void OllamaModelInstalledInfoTest::shouldGenerateModelName_data()
{
    QTest::addColumn<QString>("modelname");
    QTest::addColumn<QString>("displaymodelname");
    QTest::newRow("test1") << QStringLiteral("reader-lm:0.5b") << QStringLiteral("Reader Lm");
    QTest::newRow("test2") << QStringLiteral("deepseek:0.5b") << QStringLiteral("Deepseek");
    QTest::newRow("test3") << QStringLiteral("reader-lm") << QStringLiteral("Reader Lm");
}

void OllamaModelInstalledInfoTest::shouldGenerateModelName()
{
    QFETCH(QString, modelname);
    QFETCH(QString, displaymodelname);
    QCOMPARE(OllamaModelInstalledInfo::convertModelNameToDisplay(modelname), displaymodelname);
}

#include "moc_ollamamodelinstalledinfotest.cpp"
