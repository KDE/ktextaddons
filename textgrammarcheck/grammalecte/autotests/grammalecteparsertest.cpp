/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteparsertest.h"
#include "grammalecte/grammalecteparser.h"
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammalecteParserTest)
using namespace Qt::Literals::StringLiterals;
GrammalecteParserTest::GrammalecteParserTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteParserTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("numberOfElement");
    QTest::newRow("noerror") << u"noerror"_s << 0;
    QTest::newRow("noerror2") << u"noerror2"_s << 0;
    QTest::newRow("result2") << u"result2"_s << 3;
}

void GrammalecteParserTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, numberOfElement);
    const QString originalJsonFile = QLatin1StringView(GRAMMALECTE_DATA_DIR) + u'/' + fileName + u".json"_s;
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    TextGrammarCheck::GrammalecteParser parser;
    QCOMPARE(parser.parseResult(fields).count(), numberOfElement);
}

#include "moc_grammalecteparsertest.cpp"
