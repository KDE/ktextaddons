/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lingvaengineutiltest.h"
using namespace Qt::Literals::StringLiterals;

#include "../lingvaengineutil.h"
#include <QTest>
QTEST_MAIN(LingvaEngineUtilTest)
LingvaEngineUtilTest::LingvaEngineUtilTest(QObject *parent)
    : QObject{parent}
{
}

void LingvaEngineUtilTest::shouldHaveDefaultValues()
{
    QCOMPARE(LingvaEngineUtil::groupName(), u"LingvaTranslator"_s);
    QCOMPARE(LingvaEngineUtil::serverUrlKey(), u"ServerUrl"_s);
}

#include "moc_lingvaengineutiltest.cpp"
