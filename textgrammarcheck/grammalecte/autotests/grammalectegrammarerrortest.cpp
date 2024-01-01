/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectegrammarerrortest.h"
#include "grammalecte/grammalectegrammarerror.h"
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammalecteGrammarErrorTest)

GrammalecteGrammarErrorTest::GrammalecteGrammarErrorTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteGrammarErrorTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::GrammalecteGrammarError info;
    QCOMPARE(info.length(), -1);
    QCOMPARE(info.start(), -1);
    QCOMPARE(info.blockId(), -1);
    QVERIFY(info.error().isEmpty());
    QVERIFY(info.suggestions().isEmpty());
    QVERIFY(!info.color().isValid());
    QVERIFY(!info.isValid());
}

void GrammalecteGrammarErrorTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("nbBlock");
    QTest::addColumn<TextGrammarCheck::GrammalecteGrammarError>("error");
    QTest::newRow("empty-error") << QStringLiteral("empty-error") << 1 << TextGrammarCheck::GrammalecteGrammarError();
    TextGrammarCheck::GrammalecteGrammarError err;
    err.setBlockId(1);
    err.setStart(15);
    err.setLength(5);
    err.setColor(QColor(217, 128, 38));
    err.setSuggestions(QStringList() << QStringLiteral("Alors"));
    err.setError(QStringLiteral("Après un point, une majuscule est généralement requise."));
    err.setOption(QStringLiteral("maj"));
    err.setRule(QStringLiteral("majuscule_après_point"));
    QTest::newRow("error1") << QStringLiteral("error1") << 1 << err;
    err.setColor(QColor());
    QTest::newRow("empty-color") << QStringLiteral("empty-color") << 1 << err;
}

void GrammalecteGrammarErrorTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, nbBlock);
    QFETCH(TextGrammarCheck::GrammalecteGrammarError, error);
    const QString originalJsonFile = QLatin1String(GRAMMALECTE_DATA_DIR) + QLatin1Char('/') + fileName + QStringLiteral(".json");
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    TextGrammarCheck::GrammalecteGrammarError parser;
    parser.parse(fields, nbBlock);
    const bool compare = (parser == error);
    if (!compare) {
        qDebug() << " Parser " << parser;
        qDebug() << " error " << error;
    }
    QVERIFY(compare);
}

#include "moc_grammalectegrammarerrortest.cpp"
