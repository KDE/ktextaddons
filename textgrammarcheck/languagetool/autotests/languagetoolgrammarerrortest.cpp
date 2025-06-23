/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgrammarerrortest.h"
#include "languagetool/languagetoolgrammarerror.h"
#include <QJsonDocument>
#include <QTest>
QTEST_GUILESS_MAIN(LanguageToolGrammarErrorTest)
using namespace Qt::Literals::StringLiterals;
LanguageToolGrammarErrorTest::LanguageToolGrammarErrorTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolGrammarErrorTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("nbBlock");
    QTest::addColumn<TextGrammarCheck::LanguageToolGrammarError>("error");
    TextGrammarCheck::LanguageToolGrammarError err;
    err.setBlockId(1);
    err.setStart(3);
    err.setLength(8);
    err.setColor(QColor(Qt::red));
    err.setSuggestions(QStringList() << u"ne suis pas"_s);
    err.setError(u"Voulez-vous écrire \"ne suis pas\" ?"_s);
    // err.setOption(u"maj"_s);
    err.setRule(u"P_V_PAS"_s);
    err.setUrl(u"http://www.academie-francaise.fr/ne"_s);
    QTest::newRow("parse-error1") << u"parse-error1"_s << 1 << err;
}

void LanguageToolGrammarErrorTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, nbBlock);
    QFETCH(TextGrammarCheck::LanguageToolGrammarError, error);
    const QString originalJsonFile = QLatin1StringView(LANGUAGETOOL_DATA_DIR) + u'/' + fileName + u".json"_s;
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    TextGrammarCheck::LanguageToolGrammarError parser;
    parser.setTesting(true);
    parser.parse(fields, nbBlock);
    const bool compare = (parser == error);
    if (!compare) {
        qDebug() << " Parser " << parser;
        qDebug() << " error " << error;
    }
    QVERIFY(compare);
}

#include "moc_languagetoolgrammarerrortest.cpp"
