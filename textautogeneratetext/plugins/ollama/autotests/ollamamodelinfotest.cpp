/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfotest.h"
#include "modelsmanager/ollamamodelinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaModelInfoTest)

OllamaModelInfoTest::OllamaModelInfoTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInfoTest::shouldHaveDefaultValues()
{
    OllamaModelInfo w;
    QVERIFY(w.author().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.languages().isEmpty());
    QVERIFY(!w.isValid());
}

#include "moc_ollamamodelinfotest.cpp"
