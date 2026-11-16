/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textmessagewidgettest.h"
#include "textmessagewidget.h"

#include <KMessageWidget>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextMessageWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextMessageWidgetTest::TextMessageWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextMessageWidgetTest::shouldHaveDefaultValues()
{
    TextAddonsWidgets::TextMessageWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mMessageWidget = w.findChild<KMessageWidget *>(u"mMessageWidget"_s);
    QVERIFY(mMessageWidget);
    QVERIFY(!mMessageWidget->isCloseButtonVisible());
    QCOMPARE(mMessageWidget->position(), KMessageWidget::Position::Inline);
    QVERIFY(!mMessageWidget->wordWrap());
}

#include "moc_textmessagewidgettest.cpp"
