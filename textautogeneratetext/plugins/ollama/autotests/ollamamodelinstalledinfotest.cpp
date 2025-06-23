/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfotest.h"
using namespace Qt::Literals::StringLiterals;

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
    QTest::newRow("test1") << u"reader-lm:0.5b"_s << u"Reader Lm"_s;
    QTest::newRow("test2") << u"deepseek:0.5b"_s << u"Deepseek"_s;
    QTest::newRow("test3") << u"reader-lm"_s << u"Reader Lm"_s;
}

void OllamaModelInstalledInfoTest::shouldGenerateModelName()
{
    QFETCH(QString, modelname);
    QFETCH(QString, displaymodelname);
    QCOMPARE(OllamaModelInstalledInfo::convertModelNameToDisplay(modelname), displaymodelname);
}

#include "moc_ollamamodelinstalledinfotest.cpp"
