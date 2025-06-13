/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotinstancefoundwidgettest.h"
#include "widgets/common/textautogeneratenotinstancefoundwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateNotInstanceFoundWidgetTest)

TextAutoGenerateNotInstanceFoundWidgetTest::TextAutoGenerateNotInstanceFoundWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateNotInstanceFoundWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateNotInstanceFoundWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

#include "moc_textautogeneratenotinstancefoundwidgettest.cpp"
