/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatortest.h"
#include "translator.h"
#include <QJsonDocument>
#include <QTest>
QTEST_GUILESS_MAIN(TranslatorTest)
TranslatorTest::TranslatorTest(QObject *parent)
    : QObject{parent}
{
}

void TranslatorTest::shouldHaveDefaultValues()
{
    Translator w;
    QVERIFY(w.shortName().isEmpty());
    QVERIFY(w.modelName().isEmpty());
    QVERIFY(w.source().isEmpty());
    QVERIFY(w.checkSum().isEmpty());
    QVERIFY(w.target().isEmpty());
    QVERIFY(w.url().isEmpty());
    QVERIFY(w.repository().isEmpty());
    QVERIFY(w.type().isEmpty());
    QCOMPARE(w.version(), -1);
    QCOMPARE(w.api(), -1);
    QVERIFY(!w.isValid());
    QVERIFY(w.remote());
}

void TranslatorTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<Translator>("result");
    QTest::addColumn<bool>("isValid");
    QTest::newRow("empty") << QStringLiteral("empty") << Translator() << false;
}

void TranslatorTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(Translator, result);
    QFETCH(bool, isValid);
    const QString originalJsonFile = QLatin1String(BERGAMOT_DATA_DIR) + QStringLiteral("/translator/") + fileName + QStringLiteral(".json");
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    Translator parser;
    parser.parse(fields);
    const bool compare = (parser == result);
    if (!compare) {
        qDebug() << " Parser " << parser;
        qDebug() << " result " << result;
    }
    QVERIFY(compare);
    QCOMPARE(parser.isValid(), isValid);
}
#include "moc_translatortest.cpp"
