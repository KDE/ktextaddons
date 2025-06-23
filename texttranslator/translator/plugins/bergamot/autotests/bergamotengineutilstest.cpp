/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineutilstest.h"
using namespace Qt::Literals::StringLiterals;

#include "bergamotengineutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(BergamotEngineUtilsTest)
BergamotEngineUtilsTest::BergamotEngineUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineUtilsTest::shouldDefaultBergamotRepository()
{
    QCOMPARE(BergamotEngineUtils::defaultBergamotRepository(), u"https://translatelocally.com/models.json"_s);
    QCOMPARE(BergamotEngineUtils::groupName(), u"BergamotTranslator"_s);
    QCOMPARE(BergamotEngineUtils::coreNumberKey(), u"CoreNumber"_s);
    QCOMPARE(BergamotEngineUtils::memoryByThreadKey(), u"MemoryByThread"_s);
    QCOMPARE(BergamotEngineUtils::useLocalCacheKey(), u"UseLocalKey"_s);
}

void BergamotEngineUtilsTest::shouldExtractInfoFromLanguageLocallyStored()
{
    {
        const QString originalDir = QLatin1String(BERGAMOT_DATA_DIR) + u"/test-stored-languages/test1"_s;
        const QVector<BergamotEngineUtils::LanguageInstalled> list = BergamotEngineUtils::languageLocallyStored(originalDir);
        QCOMPARE(list.count(), 0);
    }
    {
        const QString originalDir = QLatin1String(BERGAMOT_DATA_DIR) + u"/test-stored-languages/test2"_s;
        const QVector<BergamotEngineUtils::LanguageInstalled> list = BergamotEngineUtils::languageLocallyStored(originalDir);
        QCOMPARE(list.count(), 3);
    }
}

#include "moc_bergamotengineutilstest.cpp"
