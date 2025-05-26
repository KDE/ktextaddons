/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfossortproxymodeltest.h"
#include "modelsmanager/ollamamodelavailableinfossortproxymodel.h"
#include <QTest>
QTEST_MAIN(OllamaModelAvailableInfosSortProxyModelTest)

OllamaModelAvailableInfosSortProxyModelTest::OllamaModelAvailableInfosSortProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelAvailableInfosSortProxyModelTest::shouldHaveDefaultValues()
{
    OllamaModelAvailableInfosSortProxyModel w;
    QVERIFY(w.categories().isEmpty());
    QCOMPARE(w.filterCaseSensitivity(), Qt::CaseInsensitive);
}

#include "moc_ollamamodelavailableinfossortproxymodeltest.cpp"
