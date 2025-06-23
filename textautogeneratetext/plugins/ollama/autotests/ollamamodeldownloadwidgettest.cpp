/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    OllamaModelDownloadWidget w(QString{}, QString{}, false);
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    // QVERIFY(mainLayout);
    //  QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto labelTag = w.findChild<QLabel *>(u"labelTag"_s);
    QVERIFY(labelTag);

    auto labelSize = w.findChild<QLabel *>(u"labelSize"_s);
    QVERIFY(labelSize);

    auto toolButton = w.findChild<QToolButton *>(u"toolButton"_s);
    QVERIFY(toolButton);
    QVERIFY(toolButton->autoRaise());
}

void OllamaModelDownloadWidgetTest::shouldVerifyName()
{
    const QString tag = u"bla1"_s;
    OllamaModelDownloadWidget w(tag, QString{}, false);

    auto labelTag = w.findChild<QLabel *>(u"labelTag"_s);
    QCOMPARE(labelTag->text(), tag);
}

void OllamaModelDownloadWidgetTest::shouldEmitDownloadModel()
{
    const QString name = u"bla1"_s;
    const QString size = u"32G"_s;
    OllamaModelDownloadWidget w(name, size, false);
    QSignalSpy spy(&w, &OllamaModelDownloadWidget::downloadModel);

    auto toolButton = w.findChild<QToolButton *>(u"toolButton"_s);
    QTest::mouseClick(toolButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), name);
}

#include "moc_ollamamodeldownloadwidgettest.cpp"
