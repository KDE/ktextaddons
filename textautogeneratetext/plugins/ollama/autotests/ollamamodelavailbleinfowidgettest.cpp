/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailbleinfowidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "modelsmanager/ollamamodelavailableinfowidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelAvailbleInfoWidgetTest)
OllamaModelAvailbleInfoWidgetTest::OllamaModelAvailbleInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelAvailbleInfoWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelAvailableInfoWidget w(nullptr);
    auto mMainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mMainLayout);
    QCOMPARE(mMainLayout->contentsMargins(), QMargins());
    // TODO
}

#include "moc_ollamamodelavailbleinfowidgettest.cpp"
