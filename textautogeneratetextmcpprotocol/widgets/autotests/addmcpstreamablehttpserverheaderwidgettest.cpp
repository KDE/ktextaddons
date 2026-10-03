/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstreamablehttpserverheaderwidgettest.h"
#include "server/addmcpstreamablehttpserverheaderwidget.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTest>
QTEST_MAIN(AddMcpStreamableHttpServerHeaderWidgetTest)
using namespace Qt::Literals::StringLiterals;
AddMcpStreamableHttpServerHeaderWidgetTest::AddMcpStreamableHttpServerHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpStreamableHttpServerHeaderWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpStreamableHttpServerHeaderWidget w;

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mListBox = w.findChild<QListWidget *>(u"mListBox"_s);
    QVERIFY(mListBox);
    QCOMPARE(mListBox->count(), 0);

    auto addHeaderButton = w.findChild<QPushButton *>(u"addHeaderButton"_s);
    QVERIFY(addHeaderButton);
    QVERIFY(addHeaderButton->isEnabled());

    auto modifyHeaderButton = w.findChild<QPushButton *>(u"modifyHeaderButton"_s);
    QVERIFY(modifyHeaderButton);
    QVERIFY(!modifyHeaderButton->isEnabled());

    auto removeHeaderButton = w.findChild<QPushButton *>(u"removeHeaderButton"_s);
    QVERIFY(removeHeaderButton);
    QVERIFY(!removeHeaderButton->isEnabled());

    QVERIFY(w.headers().isEmpty());
}

void AddMcpStreamableHttpServerHeaderWidgetTest::shouldEnableButtonsWhenItemSelected()
{
    TextAutoGenerateTextMcpProtocolWidgets::AddMcpStreamableHttpServerHeaderWidget w;
    const QStringList headers{u"Authorization: Bearer foo"_s, u"X-Test: bla"_s};
    w.setHeaders(headers);
    QCOMPARE(w.headers(), headers);

    auto mListBox = w.findChild<QListWidget *>(u"mListBox"_s);
    auto modifyHeaderButton = w.findChild<QPushButton *>(u"modifyHeaderButton"_s);
    auto removeHeaderButton = w.findChild<QPushButton *>(u"removeHeaderButton"_s);
    QVERIFY(!modifyHeaderButton->isEnabled());
    QVERIFY(!removeHeaderButton->isEnabled());

    mListBox->setCurrentRow(1);
    QVERIFY(modifyHeaderButton->isEnabled());
    QVERIFY(removeHeaderButton->isEnabled());

    mListBox->clearSelection();
    QVERIFY(!modifyHeaderButton->isEnabled());
    QVERIFY(!removeHeaderButton->isEnabled());
}
#include "moc_addmcpstreamablehttpserverheaderwidgettest.cpp"
