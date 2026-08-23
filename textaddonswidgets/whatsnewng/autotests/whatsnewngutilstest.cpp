/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewngutilstest.h"
#include "whatsnewng/whatsnewngutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(WhatsNewNgUtilsTest)
using namespace Qt::Literals::StringLiterals;
WhatsNewNgUtilsTest::WhatsNewNgUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void WhatsNewNgUtilsTest::shouldHaveDefaultValues()
{
    QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::allVersion(), -1);
}

void WhatsNewNgUtilsTest::shouldGenerateCreateMD5()
{
    {
        const QString foo = u"kde"_s;
        QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::createMD5(foo), u"GGzyi3byJk6f6o/PkctPXQ=="_s);
    }
    {
        const QString foo = u"été?"_s;
        QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::createMD5(foo), u"2Io+1R/a7zqqckvcwqVl1A=="_s);
    }
    {
        const QString foo = u"ete?"_s;
        QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::createMD5(foo), u"eCXMrP5HOSHKOMYmiUofrw=="_s);
    }
}
#include "moc_whatsnewngutilstest.cpp"
