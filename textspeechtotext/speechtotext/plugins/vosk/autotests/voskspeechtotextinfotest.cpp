/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextinfotest.h"
using namespace Qt::Literals::StringLiterals;

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
    QVERIFY(w.identifier().isEmpty());
    QVERIFY(w.langText().isEmpty());
    QVERIFY(w.md5().isEmpty());
    QVERIFY(w.version().isEmpty());
    QVERIFY(w.url().isEmpty());
    QCOMPARE(w.size(), 0);
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.type().isEmpty());
    QVERIFY(!w.obsolete());
}

void VoskSpeechToTextInfoTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<VoskSpeechToTextInfo>("result");
    QTest::addColumn<bool>("isValid");
    QTest::newRow("empty") << u"empty"_s << VoskSpeechToTextInfo() << false;
    VoskSpeechToTextInfo info;
    info.setLangText(u"Ukrainian"_s);
    info.setIdentifier(u"ua"_s);
    info.setMd5(u"138fb6e39f858619527030f064c0a8fc"_s);
    info.setObsolete(false);
    info.setSize(371048965);
    info.setName(u"vosk-model-uk-v3"_s);
    info.setType(u"big"_s);
    info.setUrl(u"https://alphacephei.com/vosk/models/vosk-model-uk-v3.zip"_s);
    info.setVersion(u"v3"_s);
    QTest::newRow("test1") << u"test1"_s << info << true;
}

void VoskSpeechToTextInfoTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(VoskSpeechToTextInfo, result);
    QFETCH(bool, isValid);
    const QString originalJsonFile = QLatin1String(VOSK_DATA_DIR) + u"/info/"_s + fileName + u".json"_s;
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
