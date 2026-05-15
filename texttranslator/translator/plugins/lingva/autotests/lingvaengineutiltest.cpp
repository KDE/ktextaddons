/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lingvaengineutiltest.h"

#include "../lingvaengineutil.h"
#include <QTest>
QTEST_MAIN(LingvaEngineUtilTest)
using namespace Qt::Literals::StringLiterals;
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
