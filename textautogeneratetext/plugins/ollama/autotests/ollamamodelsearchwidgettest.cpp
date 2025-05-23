/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsearchwidgettest.h"
#include "modelsmanager/ollamamodelsearchwidget.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(OllamaModelSearchWidgetTest)
OllamaModelSearchWidgetTest::OllamaModelSearchWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelSearchWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelSearchWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(mSearchLineEdit->placeholderText().isEmpty());
}

#include "moc_ollamamodelsearchwidgettest.cpp"
