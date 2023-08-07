/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineutilstest.h"
#include "bergamotengineutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(BergamotEngineUtilsTest)
BergamotEngineUtilsTest::BergamotEngineUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineUtilsTest::shouldDefaultBergamotRepository()
{
    QCOMPARE(BergamotEngineUtils::defaultBergamotRepository(), QStringLiteral("https://translatelocally.com/models.json"));
    QCOMPARE(BergamotEngineUtils::groupName(), QStringLiteral("BergamotTranslator"));
    QCOMPARE(BergamotEngineUtils::coreNumberKey(), QStringLiteral("CoreNumber"));
    QCOMPARE(BergamotEngineUtils::memoryByThreadKey(), QStringLiteral("MemoryByThread"));
}

void BergamotEngineUtilsTest::shouldExtractInfoFromLanguageLocallyStored()
{
    {
        const QString originalDir = QLatin1String(BERGAMOT_DATA_DIR) + QStringLiteral("/test-stored-languages/test1");
        QVector<BergamotEngineUtils::LanguageInstalled> list = BergamotEngineUtils::languageLocallyStored(QDir(originalDir));
        QCOMPARE(list.count(), 0);
    }
    {
        const QString originalDir = QLatin1String(BERGAMOT_DATA_DIR) + QStringLiteral("/test-stored-languages/test2");
        QVector<BergamotEngineUtils::LanguageInstalled> list = BergamotEngineUtils::languageLocallyStored(QDir(originalDir));
        QCOMPARE(list.count(), 0);
    }
}

#include "moc_bergamotengineutilstest.cpp"
