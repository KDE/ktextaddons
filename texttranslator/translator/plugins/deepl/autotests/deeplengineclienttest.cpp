/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineclienttest.h"

#include "../deeplengineclient.h"
#include <QStandardPaths>
#include <QTest>
#include <TextTranslator/TranslatorEnginePlugin>
#include <memory>
QTEST_MAIN(DeeplEngineClientTest)

using namespace Qt::Literals::StringLiterals;
DeeplEngineClientTest::DeeplEngineClientTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void DeeplEngineClientTest::shouldHaveDefaultValues()
{
    DeeplEngineClient client;
    QCOMPARE(client.name(), u"deepl"_s);
    std::unique_ptr<TextTranslator::TranslatorEnginePlugin> plugin{client.createTranslator()};
    QVERIFY(plugin);
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(client.hasConfigurationDialog());
}

#include "moc_deeplengineclienttest.cpp"
