/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "yandexengineclienttest.h"
#include <TextTranslator/TranslatorEnginePlugin>

#include "../yandexengineclient.h"
#include <QTest>
#include <memory>
QTEST_MAIN(YandexEngineClientTest)

using namespace Qt::Literals::StringLiterals;
YandexEngineClientTest::YandexEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void YandexEngineClientTest::shouldHaveDefaultValues()
{
    YandexEngineClient client;
    QCOMPARE(client.name(), u"yandex"_s);
    std::unique_ptr<TextTranslator::TranslatorEnginePlugin> plugin{client.createTranslator()};
    QVERIFY(plugin);
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(!client.hasConfigurationDialog());
}

#include "moc_yandexengineclienttest.cpp"
