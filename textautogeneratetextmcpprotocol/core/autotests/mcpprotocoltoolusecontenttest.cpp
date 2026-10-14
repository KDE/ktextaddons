/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolusecontenttest.h"
#include "impl/mcpprotocolaudiocontent.h"
#include "impl/mcpprotocolembeddedresource.h"
#include "impl/mcpprotocolimagecontent.h"
#include "impl/mcpprotocolresourcelink.h"
#include "impl/mcpprotocoltextcontent.h"
#include "impl/mcpprotocoltoolusecontent.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolToolUseContentTest)

McpProtocolToolUseContentTest::McpProtocolToolUseContentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolUseContentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolUseContent w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.input().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.id().isEmpty());
}

void McpProtocolToolUseContentTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject obj{{"type"_L1, u"tool_use"_s}, {"id"_L1, u"id1"_s}, {"name"_L1, u"foo"_s}, {"input"_L1, QJsonObject{{"a"_L1, 1}}}};
    const McpProtocolToolUseContent content = McpProtocolToolUseContent::fromJson(obj);
    QVERIFY(content.isValid());
    QCOMPARE(McpProtocolToolUseContent::toJson(content), obj);
    for (const auto &key : {"id"_L1, "name"_L1, "input"_L1}) {
        QJsonObject incomplete = obj;
        incomplete.remove(key);
        QCOMPARE(McpProtocolToolUseContent::fromJson(incomplete), McpProtocolToolUseContent());
    }
}

#include "moc_mcpprotocoltoolusecontenttest.cpp"
