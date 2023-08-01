/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "converttexttest.h"
#include "converttext.h"
#include <QTest>

QTEST_GUILESS_MAIN(ConvertTextTest)
ConvertTextTest::ConvertTextTest(QObject *parent)
    : QObject{parent}
{
}

void ConvertTextTest::shouldHaveDefaultValues()
{
    {
        const QString str(QStringLiteral("foo"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("foo"));
    }
    {
        const QString str(QStringLiteral("numérique"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("numerique"));
    }
    {
        const QString str(QStringLiteral("téléphone"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("telephone"));
    }
    {
        const QString str(QStringLiteral("noël"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("noel"));
    }
}
