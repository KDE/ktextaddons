/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "emoticonwidgetactiontest.h"
#include "emoticonwidgetaction.h"
#include <QTest>
#include <TextEmoticonsWidgets/EmoticonWidgetActionWidget>
QTEST_MAIN(EmoticonWidgetActionTest)
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionTest::EmoticonWidgetActionTest(QObject *parent)
    : QObject{parent}
{
}

void EmoticonWidgetActionTest::shouldHaveDefaultValues()
{
    const TextEmoticonsWidgets::EmoticonWidgetAction w({});

    QCOMPARE(w.defaultWidget()->objectName(), u"mEmoticonWidgetActionWidget"_s);
}

#include "moc_emoticonwidgetactiontest.cpp"
