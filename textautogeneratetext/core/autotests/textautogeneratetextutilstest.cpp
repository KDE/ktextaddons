/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextutilstest.h"
#include "core/textautogeneratetextutils.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(TextAutoGenerateTextUtilsTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextUtilsTest::TextAutoGenerateTextUtilsTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextUtilsTest::shouldHaveDefaultValues()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextUtils::instanceConfigFileName(), u"autogeneratetextinstances"_s);
}

#include "moc_textautogeneratetextutilstest.cpp"
