/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolroottest.h"
#include "impl/mcpprotocolroot.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolRootTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolRootTest::McpProtocolRootTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRootTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot w;
    QVERIFY(w.uri().isEmpty());
    QVERIFY(!w.name().has_value());
    QVERIFY(!w.meta().has_value());
}

void McpProtocolRootTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot;
    const QJsonObject obj{{"uri"_L1, u"file:///home/user/project"_s}, {"name"_L1, u"project"_s}};
    const McpProtocolRoot root = McpProtocolRoot::fromJson(obj);
    QVERIFY(root.isValid());
    QCOMPARE(McpProtocolRoot::toJson(root), obj);
    QVERIFY(!McpProtocolRoot().isValid());
    QCOMPARE(McpProtocolRoot::fromJson(QJsonObject{{"name"_L1, u"project"_s}}), McpProtocolRoot());
}

#include "moc_mcpprotocolroottest.cpp"
