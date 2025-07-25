/*
  SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importkmailautocorrectiontest.h"
using namespace Qt::Literals::StringLiterals;

#include "import/importkmailautocorrection.h"
#include <QTest>
QTEST_MAIN(ImportKMailAutocorrectionTest)

ImportKMailAutocorrectionTest::ImportKMailAutocorrectionTest(QObject *parent)
    : QObject(parent)
{
}

void ImportKMailAutocorrectionTest::shouldHaveDefaultValues()
{
    TextAutoCorrectionCore::ImportKMailAutocorrection import;
    QVERIFY(import.upperCaseExceptions().isEmpty());
    QVERIFY(import.twoUpperLetterExceptions().isEmpty());
    QVERIFY(import.autocorrectEntries().isEmpty());
    QVERIFY(import.superScriptEntries().isEmpty());

    QCOMPARE(import.typographicSingleQuotes().begin, QChar());
    QCOMPARE(import.typographicSingleQuotes().end, QChar());
    QCOMPARE(import.typographicDoubleQuotes().begin, QChar());
    QCOMPARE(import.typographicDoubleQuotes().end, QChar());

    QCOMPARE(import.maxFindStringLenght(), 0);
    QCOMPARE(import.minFindStringLenght(), 0);
}

void ImportKMailAutocorrectionTest::shouldLoadFile()
{
    const QString originalFile = QLatin1StringView(AUTOCORRECTION_DATA_DIR) + u"/custom-fr.xml"_s;
    TextAutoCorrectionCore::ImportKMailAutocorrection import;
    QString messageError;
    QVERIFY(import.import(originalFile, messageError));
    QCOMPARE(import.typographicSingleQuotes().begin, u"‘"_s);
    QCOMPARE(import.typographicSingleQuotes().end, u"’"_s);
    QCOMPARE(import.typographicDoubleQuotes().begin, u"“"_s);
    QCOMPARE(import.typographicDoubleQuotes().end, u"”"_s);

    const auto resultTwoUpperLetterExceptions = import.twoUpperLetterExceptions();
    QCOMPARE(resultTwoUpperLetterExceptions.count(), 21);

    const auto resultUpperCaseExceptions = import.upperCaseExceptions();
    QCOMPARE(resultUpperCaseExceptions.count(), 45);

    const auto resultAutocorrectEntries = import.autocorrectEntries();
    QCOMPARE(resultAutocorrectEntries.count(), 1221);
}

#include "moc_importkmailautocorrectiontest.cpp"
