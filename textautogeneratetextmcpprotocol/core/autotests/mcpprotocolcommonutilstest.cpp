/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcommonutilstest.h"
#include "common/mcpprotocolcommonutils.h"
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <cctype>
QTEST_GUILESS_MAIN(McpProtocolCommonUtilsTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolCommonUtilsTest::McpProtocolCommonUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCommonUtilsTest::shouldGenerateAuthToken()
{
    const QByteArray token = TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::generateAuthToken();
    // 32 bytes encoded in base64url without padding
    QCOMPARE(token.size(), 43);
    for (const char c : token) {
        QVERIFY2(std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_', token.constData());
    }
    QVERIFY(token != TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::generateAuthToken());
}

void McpProtocolCommonUtilsTest::shouldDefineMetaGroupName()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::metaGroupName(), u"org.kde/group"_s);
}

void McpProtocolCommonUtilsTest::shouldDefineMetaGroupTitle()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::metaGroupTitle(), u"org.kde/groupTitle"_s);
}

void McpProtocolCommonUtilsTest::shouldAddToolMeta()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    McpProtocolMeta meta;
    meta.setMeta(QMap<QString, QJsonValue>{{u"other"_s, u"x"_s}});
    McpProtocolCommonUtils::addToolMeta(meta, u"foo"_s, u"bla"_s);
    QVERIFY(meta.meta().has_value());
    const auto map = meta.meta().value();
    QCOMPARE(map.value(McpProtocolCommonUtils::metaGroupName()).toString(), u"foo"_s);
    QCOMPARE(map.value(McpProtocolCommonUtils::metaGroupTitle()).toString(), u"bla"_s);
    QCOMPARE(map.value(u"other"_s).toString(), u"x"_s);
}

#include "moc_mcpprotocolcommonutilstest.cpp"
