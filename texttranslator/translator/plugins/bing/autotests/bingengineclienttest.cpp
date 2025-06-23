/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bingengineclienttest.h"
using namespace Qt::Literals::StringLiterals;

#include "../bingengineclient.h"
#include <QTest>
QTEST_MAIN(BingEngineClientTest)

BingEngineClientTest::BingEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void BingEngineClientTest::shouldHaveDefaultValues()
{
    BingEngineClient client;
    QCOMPARE(client.name(), u"bing"_s);
    QVERIFY(client.createTranslator());
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(!client.hasConfigurationDialog());
}

#include "moc_bingengineclienttest.cpp"
