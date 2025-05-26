/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfotest.h"
#include "modelsmanager/ollamamodelavailableinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaModelAvailableInfoTest)

OllamaModelAvailableInfoTest::OllamaModelAvailableInfoTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelAvailableInfoTest::shouldHaveDefaultValues()
{
    OllamaModelAvailableInfo w;
    QVERIFY(w.author().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.languages().isEmpty());
    QVERIFY(!w.isValid());
}

#include "moc_ollamamodelavailableinfotest.cpp"
