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
    {
        // Some models use ISO 639-3 codes in their shortName, they must be converted to ISO 639-1.
        const QString originalDir = QLatin1String(BERGAMOT_DATA_DIR) + u"/test-stored-languages/test3"_s;
        const QVector<BergamotEngineUtils::LanguageInstalled> list = BergamotEngineUtils::languageLocallyStored(originalDir);
        QCOMPARE(list.count(), 2);

        BergamotEngineUtils::LanguageInstalled enfr;
        enfr.from = u"en"_s;
        enfr.to = u"fr"_s;
        enfr.shortName = u"en-fr-tiny"_s;
        enfr.absoluteLanguageModelPath = originalDir + u"/enfr.student.tiny11"_s;
        enfr.version = 1;
        QCOMPARE(list.at(0), enfr);

        BergamotEngineUtils::LanguageInstalled hbseng;
        hbseng.from = u"sr"_s;
        hbseng.to = u"en"_s;
        hbseng.shortName = u"hbs-eng-tiny"_s;
        hbseng.absoluteLanguageModelPath = originalDir + u"/hbseng.student.tiny11"_s;
        hbseng.version = 1;
        QCOMPARE(list.at(1), hbseng);
    }
}

void BergamotEngineUtilsTest::shouldAdaptLangIdentifier_data()
{
    QTest::addColumn<QString>("identifier");
    QTest::addColumn<QString>("expected");
    QTest::newRow("empty") << QString() << QString();
    // ISO 639-1 codes are used as is.
    QTest::newRow("en") << u"en"_s << u"en"_s;
    QTest::newRow("fr") << u"fr"_s << u"fr"_s;
    QTest::newRow("nb") << u"nb"_s << u"nb"_s;
    // ISO 639-3 codes are converted to ISO 639-1.
    QTest::newRow("eng") << u"eng"_s << u"en"_s;
    QTest::newRow("fra") << u"fra"_s << u"fr"_s;
    QTest::newRow("ukr") << u"ukr"_s << u"uk"_s;
    QTest::newRow("srp") << u"srp"_s << u"sr"_s;
    // "hbs" (Serbo-Croatian) is a macrolanguage without an ISO 639-1 code of its own.
    QTest::newRow("hbs") << u"hbs"_s << u"sr"_s;
    // Unknown identifiers are kept unchanged.
    QTest::newRow("unknown") << u"zzz"_s << u"zzz"_s;
    QTest::newRow("not-a-code") << u"foobar"_s << u"foobar"_s;
}

void BergamotEngineUtilsTest::shouldAdaptLangIdentifier()
{
    QFETCH(QString, identifier);
    QFETCH(QString, expected);
    QCOMPARE(BergamotEngineUtils::adaptLangIdentifier(identifier), expected);
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
