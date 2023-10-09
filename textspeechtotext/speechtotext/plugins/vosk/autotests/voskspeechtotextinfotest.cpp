/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextinfotest.h"
#include "voskspeechtotextinfo.h"
#include <QJsonDocument>
#include <QTest>
QTEST_GUILESS_MAIN(VoskSpeechToTextInfoTest)
VoskSpeechToTextInfoTest::VoskSpeechToTextInfoTest(QObject *parent)
    : QObject{parent}
{
}

void VoskSpeechToTextInfoTest::shouldHaveDefaultValues()
{
    VoskSpeechToTextInfo w;
    QVERIFY(w.lang().isEmpty());
    QVERIFY(w.langText().isEmpty());
    QVERIFY(w.md5().isEmpty());
    QVERIFY(w.version().isEmpty());
    QVERIFY(w.url().isEmpty());
    QCOMPARE(w.size(), 0);
    QVERIFY(!w.obsolete());
}

void VoskSpeechToTextInfoTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<VoskSpeechToTextInfo>("result");
    QTest::addColumn<bool>("isValid");
    QTest::newRow("empty") << QStringLiteral("empty") << VoskSpeechToTextInfo() << false;
    VoskSpeechToTextInfo info;
    info.setLangText(QStringLiteral("Ukrainian"));
    info.setLang(QStringLiteral("ua"));
    info.setMd5(QStringLiteral("138fb6e39f858619527030f064c0a8fc"));
    info.setObsolete(false);
    info.setSize(371048965);
    info.setUrl(QStringLiteral("https://alphacephei.com/vosk/models/vosk-model-uk-v3.zip"));
    info.setVersion(QStringLiteral("v3"));
    QTest::newRow("test1") << QStringLiteral("test1") << info << true;
}

void VoskSpeechToTextInfoTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(VoskSpeechToTextInfo, result);
    QFETCH(bool, isValid);
    const QString originalJsonFile = QLatin1String(VOSK_DATA_DIR) + QStringLiteral("/info/") + fileName + QStringLiteral(".json");
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();
    const QJsonDocument doc = QJsonDocument::fromJson(content);
    const QJsonObject fields = doc.object();
    VoskSpeechToTextInfo parser;
    parser.parse(fields);
    const bool compare = (parser == result);
    if (!compare) {
        qDebug() << " Parser " << parser;
        qDebug() << " result " << result;
    }
    QVERIFY(compare);
    QCOMPARE(parser.isValid(), isValid);
}

#include "moc_voskspeechtotextinfotest.cpp"
