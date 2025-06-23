/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionutilstest.h"
using namespace Qt::Literals::StringLiterals;

#include "autocorrectionutils.h"
#include <QTest>
QTEST_MAIN(AutoCorrectionUtilsTest)
AutoCorrectionUtilsTest::AutoCorrectionUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void AutoCorrectionUtilsTest::shouldConvertToLibreOfficeFilename()
{
    QCOMPARE(TextAutoCorrectionCore::AutoCorrectionUtils::libreofficeFile(u"Fr_fr"_s), u"acor_Fr_fr.dat"_s);
}

void AutoCorrectionUtilsTest::shouldSplitString()
{
    QFETCH(QString, words);
    QFETCH(QStringList, result);
    const QStringList resultLst{TextAutoCorrectionCore::AutoCorrectionUtils::wordsFromSentence(words)};
    const bool equal = (resultLst == result);
    if (!equal) {
        qDebug() << "resultLst" << resultLst;
        qDebug() << "expected" << result;
    }
    QVERIFY(equal);
}

void AutoCorrectionUtilsTest::shouldSplitString_data()
{
    QTest::addColumn<QString>("words");
    QTest::addColumn<QStringList>("result");
    QTest::addRow("empty") << QString() << QStringList();
    QTest::addRow("1 word") << u"blabla"_s << QStringList({u"blabla"_s});
    QTest::addRow("no word") << u" "_s << QStringList();
    QTest::addRow("2 words") << u"blabla foo"_s << QStringList({u"blabla foo"_s, QStringLiteral("foo")});
    QTest::addRow("3 words") << u"blabla foo la"_s << QStringList({u"blabla foo la"_s, u"foo la"_s, QStringLiteral("la")});
    QTest::addRow("1 word") << u"l'blabla"_s << QStringList({u"l'blabla"_s});
}

#include "moc_autocorrectionutilstest.cpp"
