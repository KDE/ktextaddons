/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonsettingstest.h"
#include "ollamacommonsettings.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaCommonSettingsTest)
using namespace Qt::Literals::StringLiterals;
OllamaCommonSettingsTest::OllamaCommonSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCommonSettingsTest::shouldConvertKeepAliveTypeToString()
{
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeToString(OllamaCommonSettings::KeepAliveType::KeepAliveForever), u"KeepAliveForever"_s);
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeToString(OllamaCommonSettings::KeepAliveType::SetTimer), u"SetTimer"_s);
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeToString(OllamaCommonSettings::KeepAliveType::UnloadAfterUse), u"UnloadAfterUse"_s);
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeToString(OllamaCommonSettings::KeepAliveType::Unknown), QString{});
}

void OllamaCommonSettingsTest::shouldConvertKeepAliveTypeFromString()
{
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeFromString(u"KeepAliveForever"_s), OllamaCommonSettings::KeepAliveType::KeepAliveForever);
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeFromString(u"SetTimer"_s), OllamaCommonSettings::KeepAliveType::SetTimer);
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeFromString(u"UnloadAfterUse"_s), OllamaCommonSettings::KeepAliveType::UnloadAfterUse);
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeFromString(u"foo"_s), OllamaCommonSettings::KeepAliveType::Unknown);
    QCOMPARE(OllamaCommonSettings::convertKeepAliveTypeFromString({}), OllamaCommonSettings::KeepAliveType::Unknown);
}

void OllamaCommonSettingsTest::shouldHaveDefaultValues()
{
    const OllamaCommonSettings s;
    QCOMPARE(s.seed(), 0);
    QCOMPARE(s.contextWindowSize(), 16384);
    QCOMPARE(s.keepAliveMinutes(), 1);
    QVERIFY(s.currentModel().isEmpty());
    QVERIFY(s.displayName().isEmpty());
    QCOMPARE(s.keepAliveType(), OllamaCommonSettings::KeepAliveType::Unknown);
}

#include "moc_ollamacommonsettingstest.cpp"
