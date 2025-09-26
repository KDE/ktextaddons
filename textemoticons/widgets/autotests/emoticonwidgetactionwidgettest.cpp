/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "emoticonwidgetactionwidgettest.h"
#include "emoticonwidgetactionwidget.h"
#include <QHBoxLayout>
#include <QTest>
QTEST_MAIN(EmoticonWidgetActionWidgetTest)
using namespace Qt::Literals::StringLiterals;
EmoticonWidgetActionWidgetTest::EmoticonWidgetActionWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void EmoticonWidgetActionWidgetTest::shouldHaveDefaultValues()
{
    const TextEmoticonsWidgets::EmoticonWidgetActionWidget w({});

    auto mMainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mMainLayout);
    QCOMPARE(mMainLayout->contentsMargins(), QMargins{});
}

#include "moc_emoticonwidgetactionwidgettest.cpp"
