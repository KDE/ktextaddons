/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mistralutilstest.h"
#include "mistralutils.h"
#include <QTest>
QTEST_GUILESS_MAIN(MistralUtilsTest)
MistralUtilsTest::MistralUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void MistralUtilsTest::shouldHaveDefaultValues()
{
    QCOMPARE(MistralUtils::modelsPath(), QStringLiteral("/v1/models"));
    QCOMPARE(MistralUtils::chatPath(), QStringLiteral("/v1/chat/completions"));
}

#include "moc_mistralutilstest.cpp"
