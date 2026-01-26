/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bingengineclienttest.h"
#include <TextTranslator/TranslatorEnginePlugin>

#include "../bingengineclient.h"
#include <QTest>
#include <memory>
QTEST_MAIN(BingEngineClientTest)

using namespace Qt::Literals::StringLiterals;
BingEngineClientTest::BingEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void BingEngineClientTest::shouldHaveDefaultValues()
{
    BingEngineClient client;
    QCOMPARE(client.name(), u"bing"_s);
    std::unique_ptr<TextTranslator::TranslatorEnginePlugin> plugin{client.createTranslator()};
    QVERIFY(plugin);
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(!client.hasConfigurationDialog());
}

#include "moc_bingengineclienttest.cpp"
