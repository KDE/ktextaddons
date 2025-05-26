/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfossortproxymodeltest.h"
#include "modelsmanager/ollamamodelinfossortproxymodel.h"
#include <QTest>
QTEST_MAIN(OllamaModelInfosSortProxyModelTest)

OllamaModelInfosSortProxyModelTest::OllamaModelInfosSortProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInfosSortProxyModelTest::shouldHaveDefaultValues()
{
    OllamaModelInfosSortProxyModel w;
    QCOMPARE(w.categories(), OllamaModelInfo::Category::Unknown);
    QCOMPARE(w.filterCaseSensitivity(), Qt::CaseInsensitive);
}

#include "moc_ollamamodelinfossortproxymodeltest.cpp"
