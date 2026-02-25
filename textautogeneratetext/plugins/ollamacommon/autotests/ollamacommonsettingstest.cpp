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

void OllamaCommonSettingsTest::shouldConvertShareNameTypeToString()
{
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeToString(OllamaCommonSettings::ShareNameType::DoNotShare), u"DoNotShare"_s);
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeToString(OllamaCommonSettings::ShareNameType::FullName), u"FullName"_s);
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeToString(OllamaCommonSettings::ShareNameType::UserName), u"UserName"_s);
}

void OllamaCommonSettingsTest::shouldConvertShareNameTypeFromString()
{
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeFromString(u"DoNotShare"_s), OllamaCommonSettings::ShareNameType::DoNotShare);
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeFromString(u"FullName"_s), OllamaCommonSettings::ShareNameType::FullName);
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeFromString(u"UserName"_s), OllamaCommonSettings::ShareNameType::UserName);
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeFromString(u"foo"_s), OllamaCommonSettings::ShareNameType::DoNotShare);
    QCOMPARE(OllamaCommonSettings::convertShareNameTypeFromString(QString()), OllamaCommonSettings::ShareNameType::DoNotShare);
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
    QCOMPARE(s.shareNameType(), OllamaCommonSettings::ShareNameType::DoNotShare);
    QVERIFY(!s.thoughtProcessing());

    QCOMPARE(s.defaultThoughtProcessing(), false);
    QCOMPARE(s.defaultTemperature(), 0.8);
    QCOMPARE(s.defaultSeed(), 0);
    QCOMPARE(s.defaultKeepAliveMinutes(), 1);
    QCOMPARE(s.defaultContextWindowSize(), 16384);
}

#include "moc_ollamacommonsettingstest.cpp"
