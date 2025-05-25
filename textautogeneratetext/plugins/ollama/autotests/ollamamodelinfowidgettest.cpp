/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfowidgettest.h"
#include "modelsmanager/ollamamodelinfowidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelInfoWidgetTest)
OllamaModelInfoWidgetTest::OllamaModelInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInfoWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelInfoWidget w;
    auto mMainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mMainLayout);
    QCOMPARE(mMainLayout->contentsMargins(), QMargins());
    // TODO
}

#include "moc_ollamamodelinfowidgettest.cpp"
