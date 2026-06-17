/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudiocommonutilstest.h"
#include "lmstudiocommonutils.h"
#include <QTest>
QTEST_GUILESS_MAIN(LMStudioCommonUtilsTest)
using namespace Qt::Literals::StringLiterals;
LMStudioCommonUtilsTest::LMStudioCommonUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void LMStudioCommonUtilsTest::shouldHaveDefaultValues()
{
    QCOMPARE(LMStudioCommonUtils::modelsPath(), u"/api/v1/models"_s);
    QCOMPARE(LMStudioCommonUtils::responsesPath(), u"/api/responses"_s);
    QCOMPARE(LMStudioCommonUtils::completionPath(), u"/v1/completions"_s);
}
#include "moc_lmstudiocommonutilstest.cpp"
