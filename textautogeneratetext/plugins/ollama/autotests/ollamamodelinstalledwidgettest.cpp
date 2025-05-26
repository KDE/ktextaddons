/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidgettest.h"
#include "modelsmanager/ollamamodelinstalledwidget.h"
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelInstalledWidgetTest)

OllamaModelInstalledWidgetTest::OllamaModelInstalledWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelInstalledWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelInstalledWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
    QCOMPARE(mainLayout->spacing(), 0);

    auto mRemoveModelButton = w.findChild<QToolButton *>(QStringLiteral("mRemoveModelButton"));
    QVERIFY(mRemoveModelButton);
}

#include "moc_ollamamodelinstalledwidgettest.cpp"
