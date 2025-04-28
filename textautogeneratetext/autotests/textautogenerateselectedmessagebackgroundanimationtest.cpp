/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateselectedmessagebackgroundanimationtest.h"
#include "widgets/view/textautogenerateselectedmessagebackgroundanimation.h"
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(TextAutogenerateSelectedMessageBackgroundAnimationTest)
TextAutogenerateSelectedMessageBackgroundAnimationTest::TextAutogenerateSelectedMessageBackgroundAnimationTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateSelectedMessageBackgroundAnimationTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateSelectedMessageBackgroundAnimation d(nullptr);
    QVERIFY(!d.backgroundColor().isValid());
    QVERIFY(!d.modelIndex().isValid());
}

void TextAutogenerateSelectedMessageBackgroundAnimationTest::shouldEmitBackgroundColorChanged()
{
    TextAutogenerateText::TextAutogenerateSelectedMessageBackgroundAnimation d(nullptr);
    QSignalSpy backgroundColorChangedspy(&d, &TextAutogenerateText::TextAutogenerateSelectedMessageBackgroundAnimation::backgroundColorChanged);
    QColor color(Qt::red);
    d.setBackgroundColor(color);
    QCOMPARE(backgroundColorChangedspy.count(), 1);
    backgroundColorChangedspy.clear();
    d.setBackgroundColor(color);
    QCOMPARE(backgroundColorChangedspy.count(), 0);
    backgroundColorChangedspy.clear();

    QColor colorBlack(Qt::black);
    d.setBackgroundColor(colorBlack);
    QCOMPARE(backgroundColorChangedspy.count(), 1);
}

#include "moc_textautogenerateselectedmessagebackgroundanimationtest.cpp"
