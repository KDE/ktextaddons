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
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);

    auto toolButton = w.findChild<QToolButton *>(QStringLiteral("toolButton"));
    QVERIFY(toolButton);
    QVERIFY(toolButton->autoRaise());
}

void OllamaModelDownloadWidgetTest::shouldVerifyName()
{
    const QString name = QStringLiteral("bla1");
    OllamaModelDownloadWidget w(name, QString{});

    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QCOMPARE(label->text(), name);
}

void OllamaModelDownloadWidgetTest::shouldEmitDownloadModel()
{
    const QString name = QStringLiteral("bla1");
    const QString url = QStringLiteral("www.kde.org");
    OllamaModelDownloadWidget w(name, url);
    QSignalSpy spy(&w, &OllamaModelDownloadWidget::downloadModel);

    auto toolButton = w.findChild<QToolButton *>(QStringLiteral("toolButton"));
    QTest::mouseClick(toolButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), url);
}

#include "moc_ollamamodeldownloadwidgettest.cpp"
