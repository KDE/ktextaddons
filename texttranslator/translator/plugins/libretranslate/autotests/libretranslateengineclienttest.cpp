/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineclienttest.h"

#include "../libretranslateengineclient.h"
#include <QStandardPaths>
#include <QTest>
#include <TextTranslator/TranslatorEnginePlugin>
#include <memory>
QTEST_MAIN(LibreTranslateEngineClientTest)

using namespace Qt::Literals::StringLiterals;
LibreTranslateEngineClientTest::LibreTranslateEngineClientTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void LibreTranslateEngineClientTest::shouldHaveDefaultValues()
{
    LibreTranslateEngineClient client;
    QCOMPARE(client.name(), u"libretranslate"_s);
    std::unique_ptr<TextTranslator::TranslatorEnginePlugin> plugin{client.createTranslator()};
    QVERIFY(plugin);
    QVERIFY(!client.translatedName().isEmpty());
    QVERIFY(!client.supportedFromLanguages().isEmpty());
    QVERIFY(!client.supportedToLanguages().isEmpty());
    QVERIFY(client.hasConfigurationDialog());
}

#include "moc_libretranslateengineclienttest.cpp"
