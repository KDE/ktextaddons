/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotinstancefoundwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/common/textautogeneratenotinstancefoundwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>
#include <QVBoxLayout>
#include <qtestmouse.h>

QTEST_MAIN(TextAutoGenerateNotInstanceFoundWidgetTest)

TextAutoGenerateNotInstanceFoundWidgetTest::TextAutoGenerateNotInstanceFoundWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateNotInstanceFoundWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateNotInstanceFoundWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto addInstanceButton = w.findChild<QPushButton *>(u"addInstanceButton"_s);
    QVERIFY(addInstanceButton);
    QVERIFY(!addInstanceButton->text().isEmpty());
}

void TextAutoGenerateNotInstanceFoundWidgetTest::shouldEmitSignal()
{
    TextAutoGenerateText::TextAutoGenerateNotInstanceFoundWidget w;
    auto addInstanceButton = w.findChild<QPushButton *>(u"addInstanceButton"_s);

    QSignalSpy addInstanceRequested(&w, &TextAutoGenerateText::TextAutoGenerateNotInstanceFoundWidget::addInstanceRequested);
    QTest::mouseClick(addInstanceButton, Qt::LeftButton);
    QCOMPARE(addInstanceRequested.count(), 1);
}

#include "moc_textautogeneratenotinstancefoundwidgettest.cpp"
