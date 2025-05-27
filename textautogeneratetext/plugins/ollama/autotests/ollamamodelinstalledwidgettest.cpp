/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidgettest.h"
#include "modelsmanager/ollamamodelinstalledinfowidget.h"
#include "modelsmanager/ollamamodelinstalledlistview.h"
#include "modelsmanager/ollamamodelinstalledwidget.h"
#include "modelsmanager/ollamamodelsearchlineedit.h"
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

    auto mOllamaModelInstalledListView = w.findChild<OllamaModelInstalledListView *>(QStringLiteral("mOllamaModelInstalledListView"));
    QVERIFY(mOllamaModelInstalledListView);

    auto mSearchLineEdit = w.findChild<OllamaModelSearchLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);
    auto mOllamaModelInstalledInfoWidget = w.findChild<OllamaModelInstalledInfoWidget *>(QStringLiteral("mOllamaModelInstalledInfoWidget"));
    QVERIFY(mOllamaModelInstalledInfoWidget);
}

#include "moc_ollamamodelinstalledwidgettest.cpp"
