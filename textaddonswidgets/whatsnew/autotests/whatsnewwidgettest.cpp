/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewwidgettest.h"
#include "whatsnew/whatsnewcomboboxwidget.h"
#include "whatsnew/whatsnewwidget.h"
#include <QTest>
#include <QTextBrowser>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(WhatsNewWidgetTest)
WhatsNewWidgetTest::WhatsNewWidgetTest(QWidget *parent)
    : QWidget{parent}
{
}

void WhatsNewWidgetTest::shouldHaveDefaultValues()
{
    TextAddonsWidgets::WhatsNewWidget w({});
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mLabelInfo = w.findChild<QTextBrowser *>(u"mLabelInfo"_s);
    QVERIFY(mLabelInfo);
    QVERIFY(mLabelInfo->toPlainText().isEmpty());
    QVERIFY(mLabelInfo->openExternalLinks());

    auto mWhatsNewComboBoxWidget = w.findChild<TextAddonsWidgets::WhatsNewComboBoxWidget *>(u"mWhatsNewComboBoxWidget"_s);
    QVERIFY(mWhatsNewComboBoxWidget);
}

#include "moc_whatsnewwidgettest.cpp"
