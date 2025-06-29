/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaengineclienttest.h"
using namespace Qt::Literals::StringLiterals;

#include "../lingvaengineclient.h"
#include "translator/translatorengineplugin.h"
#include <QTest>
QTEST_MAIN(LingvaEngineClientTest)

LingvaEngineClientTest::LingvaEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void LingvaEngineClientTest::shouldHaveDefaultValues()
{
    LingvaEngineClient client;
    QCOMPARE(client.name(), u"lingva"_s);
    auto plugin = client.createTranslator();
    QVERIFY(plugin);
    delete plugin;
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(client.hasConfigurationDialog());
}

#include "moc_lingvaengineclienttest.cpp"
