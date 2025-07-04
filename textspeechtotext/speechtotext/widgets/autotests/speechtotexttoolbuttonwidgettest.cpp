/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotexttoolbuttonwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mToolButton = w.findChild<QToolButton *>(u"mToolButton"_s);
    QVERIFY(mToolButton);

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

#include "moc_speechtotexttoolbuttonwidgettest.cpp"
