/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolparsertest.h"
#include "languagetool/languagetoolparser.h"
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(LanguageToolParserTest)
LanguageToolParserTest::LanguageToolParserTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LanguageToolParserTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("numberOfElement");
    QTest::newRow("noerror") << u"noerror"_s << 0;
    QTest::newRow("test1") << u"test1"_s << 1;
    QTest::newRow("test2") << u"test2"_s << 3;
}

void LanguageToolParserTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, numberOfElement);
    const QString originalJsonFile = QLatin1StringView(LANGUAGETOOL_DATA_DIR) + u'/' + fileName + u".json"_s;
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    TextGrammarCheck::LanguageToolParser parser;
    QCOMPARE(parser.parseResult(fields).count(), numberOfElement);
}

#include "moc_languagetoolparsertest.cpp"
