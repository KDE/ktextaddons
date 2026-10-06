/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextactiontest.h"

#include "speechtotext/widgets/speechtotextaction.h"
#include "textspeechtotext/speechtotextmanager.h"
#include <QSignalSpy>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(SpeechToTextActionTest)
SpeechToTextActionTest::SpeechToTextActionTest(QObject *parent)
    : QObject{parent}
{
}

void SpeechToTextActionTest::shouldHaveDefaultValues()
{
    TextSpeechToText::SpeechToTextAction w;
    QVERIFY(w.isCheckable());
    QVERIFY(!w.isChecked());
}

void SpeechToTextActionTest::shouldEmitTextAvailableOnlyForRequester()
{
    TextSpeechToText::SpeechToTextAction w;
    TextSpeechToText::SpeechToTextAction other;
    QSignalSpy spy(&w, &TextSpeechToText::SpeechToTextAction::textAvailable);
    QSignalSpy otherSpy(&other, &TextSpeechToText::SpeechToTextAction::textAvailable);

    Q_EMIT TextSpeechToText::SpeechToTextManager::self()->speechToTextDoneFor(&w, u"foo"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), u"foo"_s);
    QCOMPARE(otherSpy.count(), 0);

    // No requester (old API): nobody gets the text
    Q_EMIT TextSpeechToText::SpeechToTextManager::self()->speechToTextDoneFor(nullptr, u"bla"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(otherSpy.count(), 0);
}

#include "moc_speechtotextactiontest.cpp"
