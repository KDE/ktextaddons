/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditwidgettest.h"

#include "widgets/common/textautogeneratetextlineedit.h"
#include "widgets/common/textautogeneratetextlineeditwidget.h"

#include <QHBoxLayout>
#include <QTest>
#include <QToolButton>
using namespace Qt::Literals::StringLiterals;
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
    QCOMPARE(mainLayout->spacing(), 0);

    auto mTextAutoGenerateTextLineEdit = w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEdit *>(u"mTextAutoGenerateTextLineEdit"_s);
    QVERIFY(mTextAutoGenerateTextLineEdit);

    auto mSendMessage = w.findChild<QToolButton *>(u"mSendMessage"_s);
    QVERIFY(mSendMessage);
    QVERIFY(mSendMessage->text().isEmpty());
    QVERIFY(!mSendMessage->isEnabled());
    QVERIFY(!mSendMessage->toolTip().isEmpty());

    auto mAttachFile = w.findChild<QToolButton *>(u"mAttachFile"_s);
    QVERIFY(mAttachFile);
    QVERIFY(mAttachFile->text().isEmpty());
    QVERIFY(!mAttachFile->isEnabled());
    QVERIFY(!mAttachFile->toolTip().isEmpty());
}

void TextAutoGenerateTextLineEditWidgetTest::shouldEnableButton()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEditWidget w(nullptr);
    auto mTextAutoGenerateTextLineEdit = w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEdit *>(u"mTextAutoGenerateTextLineEdit"_s);
    QVERIFY(mTextAutoGenerateTextLineEdit);

    auto mSendMessage = w.findChild<QToolButton *>(u"mSendMessage"_s);
    QVERIFY(mSendMessage);
    QVERIFY(!mSendMessage->isEnabled());

    mTextAutoGenerateTextLineEdit->setText(u"foo"_s);
    QVERIFY(mSendMessage->isEnabled());

    mTextAutoGenerateTextLineEdit->clear();
    QVERIFY(!mSendMessage->isEnabled());
}

#include "moc_textautogeneratetextlineeditwidgettest.cpp"
