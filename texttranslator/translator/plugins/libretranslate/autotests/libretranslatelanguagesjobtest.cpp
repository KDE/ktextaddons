/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslatelanguagesjobtest.h"
#include "../libretranslatelanguagesjob.h"
#include <QTest>
QTEST_GUILESS_MAIN(LibreTranslateLanguagesJobTest)

using namespace Qt::Literals::StringLiterals;
LibreTranslateLanguagesJobTest::LibreTranslateLanguagesJobTest(QObject *parent)
    : QObject{parent}
{
}

void LibreTranslateLanguagesJobTest::shouldHaveDefaultValues()
{
    LibreTranslateLanguagesJob job;
    QVERIFY(!job.canStart());
    QVERIFY(job.info().serverUrl.isEmpty());
    job.setInfo({.serverUrl = u"https://libretranslate.com"_s});
    QVERIFY(job.canStart());
}

void LibreTranslateLanguagesJobTest::shouldParseLanguages()
{
    const QByteArray data = R"([
        {"code":"en","name":"English","targets":["en","de","fr"]},
        {"code":"de","name":"German","targets":["de","en"]}
    ])";
    const QMap<QString, QStringList> languages = LibreTranslateLanguagesJob::parseLanguages(data);
    QCOMPARE(languages.count(), 2);
    QCOMPARE(languages.value(u"en"_s), QStringList({u"de"_s, u"fr"_s}));
    QCOMPARE(languages.value(u"de"_s), QStringList({u"en"_s}));
}

void LibreTranslateLanguagesJobTest::shouldIgnoreInvalidLanguages()
{
    QVERIFY(LibreTranslateLanguagesJob::parseLanguages({}).isEmpty());
    QVERIFY(LibreTranslateLanguagesJob::parseLanguages(R"({"error":"foo"})").isEmpty());
    const QMap<QString, QStringList> languages = LibreTranslateLanguagesJob::parseLanguages(R"([{"name":"Foo"},{"code":"fr"}])");
    QCOMPARE(languages.count(), 1);
    QVERIFY(languages.value(u"fr"_s).isEmpty());
}

#include "moc_libretranslatelanguagesjobtest.cpp"
