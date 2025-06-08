/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditwidgettest.h"
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

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutoGenerateTextLineEdit = w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEdit *>(QStringLiteral("mTextAutoGenerateTextLineEdit"));
    QVERIFY(mTextAutoGenerateTextLineEdit);

    auto mSendMessage = w.findChild<QPushButton *>(QStringLiteral("mSendMessage"));
    QVERIFY(mSendMessage);
    QVERIFY(!mSendMessage->text().isEmpty());
    QVERIFY(!mSendMessage->isEnabled());
}

void TextAutoGenerateTextLineEditWidgetTest::shouldEnableButton()
{
    TextAutoGenerateText::TextAutoGenerateTextLineEditWidget w(nullptr);
    auto mTextAutoGenerateTextLineEdit = w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEdit *>(QStringLiteral("mTextAutoGenerateTextLineEdit"));
    QVERIFY(mTextAutoGenerateTextLineEdit);

    auto mSendMessage = w.findChild<QPushButton *>(QStringLiteral("mSendMessage"));
    QVERIFY(mSendMessage);
    QVERIFY(!mSendMessage->isEnabled());

    mTextAutoGenerateTextLineEdit->setText(QStringLiteral("foo"));
    QVERIFY(mSendMessage->isEnabled());

    mTextAutoGenerateTextLineEdit->clear();
    QVERIFY(!mSendMessage->isEnabled());
}

#include "moc_textautogeneratetextlineeditwidgettest.cpp"
