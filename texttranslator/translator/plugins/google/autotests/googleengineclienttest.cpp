/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleengineclienttest.h"
#include "../googleengineclient.h"
#include <QTest>
#include <TextTranslator/TranslatorEnginePlugin>
#include <memory>
QTEST_MAIN(GoogleEngineClientTest)

using namespace Qt::Literals::StringLiterals;
GoogleEngineClientTest::GoogleEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void GoogleEngineClientTest::shouldHaveDefaultValues()
{
    GoogleEngineClient client;
    QCOMPARE(client.name(), u"google"_s);
    std::unique_ptr<TextTranslator::TranslatorEnginePlugin> plugin{client.createTranslator()};
    QVERIFY(plugin);
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(!client.hasConfigurationDialog());
}

#include "moc_googleengineclienttest.cpp"
