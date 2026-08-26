/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineutilstest.h"
using namespace Qt::Literals::StringLiterals;

#include "bergamotengineutils.h"
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(BergamotEngineUtilsTest)
BergamotEngineUtilsTest::BergamotEngineUtilsTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
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

void BergamotEngineUtilsTest::shouldFindModelFiles()
{
    {
        // Missing directory.
        const BergamotEngineUtils::ModelFiles files = BergamotEngineUtils::modelFiles(QLatin1String(BERGAMOT_DATA_DIR) + u"/test-model-files/unknown"_s);
        QVERIFY(!files.isValid());
    }
    {
        const QString originalDir = QLatin1String(BERGAMOT_DATA_DIR) + u"/test-model-files/enfr"_s;
        const BergamotEngineUtils::ModelFiles files = BergamotEngineUtils::modelFiles(originalDir);
        QVERIFY(files.isValid());
        QCOMPARE(files.model, originalDir + u"/model.intgemm.alphas.bin"_s);
        QCOMPARE(files.vocabulary, originalDir + u"/vocab.fren.spm"_s);
        QCOMPARE(files.shortlist, originalDir + u"/lex.s2t.bin"_s);
        QVERIFY(files.ssplit.isEmpty());
    }
    {
        // A vocabulary and a shortlist are mandatory.
        const QString originalDir = QLatin1String(BERGAMOT_DATA_DIR) + u"/test-model-files/incomplete"_s;
        const BergamotEngineUtils::ModelFiles files = BergamotEngineUtils::modelFiles(originalDir);
        QVERIFY(!files.isValid());
        QCOMPARE(files.model, originalDir + u"/model.intgemm.alphas.bin"_s);
    }
}

#include "moc_bergamotengineutilstest.cpp"
