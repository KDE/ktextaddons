/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/common/textautogeneratetextlineedit.h"
#include "widgets/common/textautogeneratetextlineeditwidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QTest>
QTEST_MAIN(TextAutoGenerateTextLineEditWidgetTest)
TextAutoGenerateTextLineEditWidgetTest::TextAutoGenerateTextLineEditWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextLineEditWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEditWidget w(nullptr);

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutoGenerateTextLineEdit = w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEdit *>(u"mTextAutoGenerateTextLineEdit"_s);
    QVERIFY(mTextAutoGenerateTextLineEdit);

    auto mSendMessage = w.findChild<QPushButton *>(u"mSendMessage"_s);
    QVERIFY(mSendMessage);
    QVERIFY(!mSendMessage->text().isEmpty());
    QVERIFY(!mSendMessage->isEnabled());
}

void TextAutoGenerateTextLineEditWidgetTest::shouldEnableButton()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEditWidget w(nullptr);
    auto mTextAutoGenerateTextLineEdit = w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEdit *>(u"mTextAutoGenerateTextLineEdit"_s);
    QVERIFY(mTextAutoGenerateTextLineEdit);

    auto mSendMessage = w.findChild<QPushButton *>(u"mSendMessage"_s);
    QVERIFY(mSendMessage);
    QVERIFY(!mSendMessage->isEnabled());

    mTextAutoGenerateTextLineEdit->setText(u"foo"_s);
    QVERIFY(mSendMessage->isEnabled());

    mTextAutoGenerateTextLineEdit->clear();
    QVERIFY(!mSendMessage->isEnabled());
}

#include "moc_textautogeneratetextlineeditwidgettest.cpp"
