/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadfromnamewidgettest.h"
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mModelNameLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mModelNameLineEdit"));
    QVERIFY(mModelNameLineEdit);
    QVERIFY(mModelNameLineEdit->text().isEmpty());

    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
}

#include "moc_ollamamodeldownloadfromnamewidgettest.cpp"
