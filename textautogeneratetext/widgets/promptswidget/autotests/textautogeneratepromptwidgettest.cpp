/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratepromptwidgettest.h"
#include "widgets/promptswidget/textautogeneratepromptwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTest>
QTEST_MAIN(TextAutoGeneratePromptWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGeneratePromptWidgetTest::TextAutoGeneratePromptWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGeneratePromptWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGeneratePromptWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QVERIFY(mName->text().isEmpty());

    auto mText = w.findChild<QPlainTextEdit *>(u"mText"_s);
    QVERIFY(mText);
    QVERIFY(mText->toPlainText().isEmpty());
}

#include "moc_textautogeneratepromptwidgettest.cpp"
