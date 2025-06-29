/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "libretranslateengineutiltest.h"
using namespace Qt::Literals::StringLiterals;

#include "../libretranslateengineutil.h"
#include <QTest>
QTEST_MAIN(LibreTranslateEngineUtilTest)
LibreTranslateEngineUtilTest::LibreTranslateEngineUtilTest(QObject *parent)
    : QObject{parent}
{
}

void LibreTranslateEngineUtilTest::shouldHaveDefaultValues()
{
    QCOMPARE(LibreTranslateEngineUtil::groupName(), u"LibreTranslateTranslator"_s);
    QCOMPARE(LibreTranslateEngineUtil::serverUrlKey(), u"ServerUrl"_s);
}

#include "moc_libretranslateengineutiltest.cpp"
