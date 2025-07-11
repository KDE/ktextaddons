/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleengineclienttest.h"
using namespace Qt::Literals::StringLiterals;

#include "../googleengineclient.h"
#include <QTest>
QTEST_MAIN(GoogleEngineClientTest)

GoogleEngineClientTest::GoogleEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void GoogleEngineClientTest::shouldHaveDefaultValues()
{
    GoogleEngineClient client;
    QCOMPARE(client.name(), u"google"_s);
    QVERIFY(client.createTranslator());
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(!client.hasConfigurationDialog());
}

#include "moc_googleengineclienttest.cpp"
