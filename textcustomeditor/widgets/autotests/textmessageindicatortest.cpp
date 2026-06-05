/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textmessageindicatortest.h"
#include "widgets/textmessageindicator.h"

#include <KMessageWidget>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextMessageIndicatorTest)
using namespace Qt::Literals::StringLiterals;
TextMessageIndicatorTest::TextMessageIndicatorTest(QObject *parent)
    : QObject{parent}
{
}

void TextMessageIndicatorTest::shouldHaveDefaultValues()
{
    TextCustomEditor::TextMessageIndicator w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mMessageWidget = w.findChild<KMessageWidget *>(u"mMessageWidget"_s);
    QVERIFY(mMessageWidget);
    QVERIFY(!mMessageWidget->isCloseButtonVisible());
    QCOMPARE(mMessageWidget->position(), KMessageWidget::Position::Inline);
    QVERIFY(!mMessageWidget->wordWrap());
}

#include "moc_textmessageindicatortest.cpp"
