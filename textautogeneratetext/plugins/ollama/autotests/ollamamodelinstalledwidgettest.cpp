/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "modelsmanager/ollamamodelinstalledinfowidget.h"
#include "modelsmanager/ollamamodelinstalledlistview.h"
#include "modelsmanager/ollamamodelinstalledwidget.h"
#include "modelsmanager/ollamamodelsearchlineedit.h"
#include <QScrollArea>
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

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
    QCOMPARE(mainLayout->spacing(), 0);

    auto mRemoveModelButton = w.findChild<QToolButton *>(u"mRemoveModelButton"_s);
    QVERIFY(mRemoveModelButton);

    auto mOllamaModelInstalledListView = w.findChild<OllamaModelInstalledListView *>(u"mOllamaModelInstalledListView"_s);
    QVERIFY(mOllamaModelInstalledListView);

    auto mSearchLineEdit = w.findChild<OllamaModelSearchLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    auto mOllamaModelInstalledInfoWidget = w.findChild<OllamaModelInstalledInfoWidget *>(u"mOllamaModelInstalledInfoWidget"_s);
    QVERIFY(mOllamaModelInstalledInfoWidget);

    auto scrollArea = w.findChild<QScrollArea *>(u"scrollArea"_s);
    QVERIFY(scrollArea);
    QCOMPARE(scrollArea->horizontalScrollBarPolicy(), Qt::ScrollBarAlwaysOff);
    QCOMPARE(scrollArea->verticalScrollBarPolicy(), Qt::ScrollBarAsNeeded);
    QVERIFY(scrollArea->widgetResizable());
}

#include "moc_ollamamodelinstalledwidgettest.cpp"
