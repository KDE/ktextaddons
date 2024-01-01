/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotexttoolbuttonwidgettest.h"
#include "speechtotext/widgets/speechtotexttoolbuttonwidget.h"
#include <QHBoxLayout>
#include <QTest>
#include <QToolButton>
QTEST_MAIN(SpeechToTextToolButtonWidgetTest)
SpeechToTextToolButtonWidgetTest::SpeechToTextToolButtonWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void SpeechToTextToolButtonWidgetTest::shouldHaveDefaultValues()
{
    TextSpeechToText::SpeechToTextToolButtonWidget w;

    auto mToolButton = w.findChild<QToolButton *>(QStringLiteral("mToolButton"));
    QVERIFY(mToolButton);

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

#include "moc_speechtotexttoolbuttonwidgettest.cpp"
