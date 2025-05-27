/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadprogresswidgettest.h"
#include "modelsmanager/ollamamodeldownloadprogresswidget.h"
#include <QLabel>
#include <QProgressBar>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelDownloadProgressWidgetTest)

OllamaModelDownloadProgressWidgetTest::OllamaModelDownloadProgressWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadProgressWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadProgressWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
    // TODO

    auto mProgressBar = w.findChild<QProgressBar *>(QStringLiteral("mProgressBar"));
    QVERIFY(mProgressBar);
    auto mModelNameLabel = w.findChild<QLabel *>(QStringLiteral("mModelNameLabel"));
    QVERIFY(mModelNameLabel);
    auto mProgressStatusLabel = w.findChild<QLabel *>(QStringLiteral("mProgressStatusLabel"));
    QVERIFY(mProgressStatusLabel);
}

#include "moc_ollamamodeldownloadprogresswidgettest.cpp"
