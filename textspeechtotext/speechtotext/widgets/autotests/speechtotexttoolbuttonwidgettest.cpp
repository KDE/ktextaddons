/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotexttoolbuttonwidgettest.h"

#include "speechtotext/widgets/speechtotexttoolbuttonwidget.h"
#include "textspeechtotext/speechtotextmanager.h"
#include <QHBoxLayout>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
using namespace Qt::Literals::StringLiterals;
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
    QVERIFY(mToolButton->isCheckable());
    QVERIFY(!mToolButton->isChecked());

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

void SpeechToTextToolButtonWidgetTest::shouldEmitTextAvailableOnlyForRequester()
{
    TextSpeechToText::SpeechToTextToolButtonWidget w;
    TextSpeechToText::SpeechToTextToolButtonWidget other;
    QSignalSpy spy(&w, &TextSpeechToText::SpeechToTextToolButtonWidget::textAvailable);
    QSignalSpy otherSpy(&other, &TextSpeechToText::SpeechToTextToolButtonWidget::textAvailable);

    Q_EMIT TextSpeechToText::SpeechToTextManager::self()->speechToTextDoneFor(&w, u"foo"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), u"foo"_s);
    QCOMPARE(otherSpy.count(), 0);

    // No requester (old API): nobody gets the text
    Q_EMIT TextSpeechToText::SpeechToTextManager::self()->speechToTextDoneFor(nullptr, u"bla"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(otherSpy.count(), 0);
}

#include "moc_speechtotexttoolbuttonwidgettest.cpp"
