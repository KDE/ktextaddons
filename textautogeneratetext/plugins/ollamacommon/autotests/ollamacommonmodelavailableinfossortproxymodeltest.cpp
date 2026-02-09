/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelavailableinfossortproxymodeltest.h"
#include "ollamacommonmodelavailableinfossortproxymodel.h"
#include <QTest>
QTEST_MAIN(OllamaCommonModelAvailableInfosSortProxyModelTest)

OllamaCommonModelAvailableInfosSortProxyModelTest::OllamaCommonModelAvailableInfosSortProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCommonModelAvailableInfosSortProxyModelTest::shouldHaveDefaultValues()
{
    const OllamaCommonModelAvailableInfosSortProxyModel w;
    QVERIFY(w.categories().isEmpty());
    QCOMPARE(w.filterCaseSensitivity(), Qt::CaseInsensitive);
}

#include "moc_ollamacommonmodelavailableinfossortproxymodeltest.cpp"
