/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfotest.h"
#include "modelsmanager/genericnetworkmodelavailableinfo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(GenericNetworkModelAvailableInfoTest)

using namespace Qt::Literals::StringLiterals;

GenericNetworkModelAvailableInfoTest::GenericNetworkModelAvailableInfoTest(QObject *parent)
    : QObject{parent}
{
}

void GenericNetworkModelAvailableInfoTest::shouldHaveDefaultValues()
{
    GenericNetworkModelAvailableInfo info;
    QVERIFY(info.description().isEmpty());
    QVERIFY(info.modelName().isEmpty());
    QVERIFY(info.modelSize().isEmpty());
    QVERIFY(info.identifier().isEmpty());
    QVERIFY(info.ownedBy().isEmpty());
    QCOMPARE(info.capabilities(), {GenericNetworkModelAvailableInfo::Capability::None});
}

void GenericNetworkModelAvailableInfoTest::shouldParseMistralCapabilities()
{
    const QByteArray data = R"({"id":"mistral-large-latest","name":"mistral-large-latest","owned_by":"mistralai",
"capabilities":{"completion_chat":true,"function_calling":true,"vision":true,"ocr":false,"audio":false}})"_ba;
    GenericNetworkModelAvailableInfo info;
    info.parseInfo(QJsonDocument::fromJson(data).object());
    QCOMPARE(info.identifier(), u"mistral-large-latest"_s);
    QCOMPARE(info.modelName(), u"mistral-large-latest"_s);
    QCOMPARE(info.ownedBy(), u"mistralai"_s);
    QCOMPARE(info.capabilities(), GenericNetworkModelAvailableInfo::Capability::Tools | GenericNetworkModelAvailableInfo::Capability::Vision);
}

void GenericNetworkModelAvailableInfoTest::shouldParseAnthropicCapabilities()
{
    const QByteArray data = R"({"id":"claude-opus-4-8","display_name":"Claude Opus 4.8","type":"model",
"capabilities":{"image_input":{"supported":true},"structured_outputs":{"supported":true},
"thinking":{"supported":true,"types":{"enabled":{"supported":false},"adaptive":{"supported":true}}}}})"_ba;
    GenericNetworkModelAvailableInfo info;
    info.parseInfo(QJsonDocument::fromJson(data).object());
    QCOMPARE(info.identifier(), u"claude-opus-4-8"_s);
    QCOMPARE(info.modelName(), u"Claude Opus 4.8"_s);
    QCOMPARE(info.capabilities(), GenericNetworkModelAvailableInfo::Capability::Vision | GenericNetworkModelAvailableInfo::Capability::Thinking);
}

#include "moc_genericnetworkmodelavailableinfotest.cpp"
