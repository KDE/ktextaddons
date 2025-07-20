/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateselectedmessagebackgroundanimationtest.h"
#include "widgets/view/textautogenerateselectedmessagebackgroundanimation.h"
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(TextAutoGenerateSelectedMessageBackgroundAnimationTest)
TextAutoGenerateSelectedMessageBackgroundAnimationTest::TextAutoGenerateSelectedMessageBackgroundAnimationTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSelectedMessageBackgroundAnimationTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSelectedMessageBackgroundAnimation d(nullptr);
    QVERIFY(!d.backgroundColor().isValid());
    QVERIFY(!d.modelIndex().isValid());
}

void TextAutoGenerateSelectedMessageBackgroundAnimationTest::shouldEmitBackgroundColorChanged()
{
    TextAutoGenerateText::TextAutoGenerateSelectedMessageBackgroundAnimation d(nullptr);
    QSignalSpy backgroundColorChangedspy(&d, &TextAutoGenerateText::TextAutoGenerateSelectedMessageBackgroundAnimation::backgroundColorChanged);
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
