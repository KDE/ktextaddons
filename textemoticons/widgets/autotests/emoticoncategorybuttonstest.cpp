/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emoticoncategorybuttonstest.h"
using namespace Qt::Literals::StringLiterals;

#include "emoticoncategorybuttons.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QTest>
QTEST_MAIN(EmoticonCategoryButtonsTest)
EmoticonCategoryButtonsTest::EmoticonCategoryButtonsTest(QObject *parent)
    : QObject{parent}
{
}

void EmoticonCategoryButtonsTest::shouldHaveDefaultValues()
{
    TextEmoticonsWidgets::EmoticonCategoryButtons w;

    auto mMainLayout = w.findChild<QHBoxLayout *>(u"mMainLayout"_s);
    QVERIFY(mMainLayout);
    QCOMPARE(mMainLayout->contentsMargins(), QMargins{});

    auto mButtonGroup = w.findChild<QButtonGroup *>(u"mButtonGroup"_s);
    QVERIFY(mButtonGroup);
    QVERIFY(mButtonGroup->buttons().isEmpty());
}

#include "moc_emoticoncategorybuttonstest.cpp"
