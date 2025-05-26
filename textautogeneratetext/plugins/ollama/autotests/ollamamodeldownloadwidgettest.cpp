/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadwidgettest.h"
#include "modelsmanager/ollamamodeldownloadwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>
QTEST_MAIN(OllamaModelDownloadWidgetTest)

OllamaModelDownloadWidgetTest::OllamaModelDownloadWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelDownloadWidgetTest::shouldHaveDefaultValues()
{
    OllamaModelDownloadWidget w(QString{}, QString{});
    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    // QVERIFY(mainLayout);
    //  QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto labelTag = w.findChild<QLabel *>(QStringLiteral("labelTag"));
    QVERIFY(labelTag);

    auto labelSize = w.findChild<QLabel *>(QStringLiteral("labelSize"));
    QVERIFY(labelSize);

    auto toolButton = w.findChild<QToolButton *>(QStringLiteral("toolButton"));
    QVERIFY(toolButton);
    QVERIFY(toolButton->autoRaise());
}

void OllamaModelDownloadWidgetTest::shouldVerifyName()
{
    const QString tag = QStringLiteral("bla1");
    OllamaModelDownloadWidget w(tag, QString{});

    auto labelTag = w.findChild<QLabel *>(QStringLiteral("labelTag"));
    QCOMPARE(labelTag->text(), tag);
}

void OllamaModelDownloadWidgetTest::shouldEmitDownloadModel()
{
    const QString name = QStringLiteral("bla1");
    const QString size = QStringLiteral("32G");
    OllamaModelDownloadWidget w(name, size);
    QSignalSpy spy(&w, &OllamaModelDownloadWidget::downloadModel);

    auto toolButton = w.findChild<QToolButton *>(QStringLiteral("toolButton"));
    QTest::mouseClick(toolButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), name);
}

#include "moc_ollamamodeldownloadwidgettest.cpp"
