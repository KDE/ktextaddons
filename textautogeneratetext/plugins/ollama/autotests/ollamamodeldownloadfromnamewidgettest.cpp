/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadfromnamewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "modelsmanager/ollamamodeldownloadfromnamewidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelDownloadFromNameWidgetTest)

OllamaModelDownloadFromNameWidgetTest::OllamaModelDownloadFromNameWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadFromNameWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadFromNameWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mModelNameLineEdit = w.findChild<QLineEdit *>(u"mModelNameLineEdit"_s);
    QVERIFY(mModelNameLineEdit);
    QVERIFY(mModelNameLineEdit->text().isEmpty());

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
}

#include "moc_ollamamodeldownloadfromnamewidgettest.cpp"
