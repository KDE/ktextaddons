/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadprogresswidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "modelsmanager/ollamamodeldownloadprogresswidget.h"
#include <QLabel>
#include <QProgressBar>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(OllamaModelDownloadProgressWidgetTest)

OllamaModelDownloadProgressWidgetTest::OllamaModelDownloadProgressWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadProgressWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadProgressWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mProgressBar = w.findChild<QProgressBar *>(u"mProgressBar"_s);
    QVERIFY(mProgressBar);
    auto mModelNameLabel = w.findChild<QLabel *>(u"mModelNameLabel"_s);
    QVERIFY(mModelNameLabel);
    auto mProgressStatusLabel = w.findChild<QLabel *>(u"mProgressStatusLabel"_s);
    QVERIFY(mProgressStatusLabel);

    auto mCancelDownloadButton = w.findChild<QToolButton *>(u"mCancelDownloadButton"_s);
    QVERIFY(mCancelDownloadButton);
    QVERIFY(!mCancelDownloadButton->toolTip().isEmpty());
}

#include "moc_ollamamodeldownloadprogresswidgettest.cpp"
