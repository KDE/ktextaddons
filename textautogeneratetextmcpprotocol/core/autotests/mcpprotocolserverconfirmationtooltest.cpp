/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfirmationtooltest.h"
#include "server/mcpprotocolserverconfirmationtool.h"
#include "server/mcpprotocolservertoolcall.h"
#include <QSignalSpy>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolServerConfirmationToolTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
class TestConfirmationTool : public McpProtocolServerConfirmationTool
{
public:
    TestConfirmationTool(ToolKind kind, bool askModify)
        : mKind(kind)
        , mAskModify(askModify)
    {
    }

    [[nodiscard]] McpProtocolTool definition() const override
    {
        return createTool(u"test_tool"_s, u"Test Tool"_s, u"Test"_s, mKind);
    }

    int mCallCount = 0;

protected:
    [[nodiscard]] bool askModify() const override
    {
        return mAskModify;
    }

private:
    void doCall(McpProtocolServerToolCall *call) override
    {
        ++mCallCount;
        call->finishWithText(u"done"_s);
    }

    const ToolKind mKind;
    const bool mAskModify;
};
}

McpProtocolServerConfirmationToolTest::McpProtocolServerConfirmationToolTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerConfirmationToolTest::shouldCallDirectlyWithoutConfirmation_data()
{
    QTest::addColumn<McpProtocolServerTool::ToolKind>("kind");
    QTest::addColumn<bool>("askModify");
    QTest::newRow("readonly-ask") << McpProtocolServerTool::ToolKind::ReadOnly << true;
    QTest::newRow("readonly-noask") << McpProtocolServerTool::ToolKind::ReadOnly << false;
    QTest::newRow("modify-noask") << McpProtocolServerTool::ToolKind::Modify << false;
    QTest::newRow("destructive-noask") << McpProtocolServerTool::ToolKind::Destructive << false;
}

void McpProtocolServerConfirmationToolTest::shouldCallDirectlyWithoutConfirmation()
{
    QFETCH(McpProtocolServerTool::ToolKind, kind);
    QFETCH(bool, askModify);
    TestConfirmationTool tool(kind, askModify);
    McpProtocolServerToolCall call(1, u"test_tool"_s, {});
    QSignalSpy resultSpy(&call, &McpProtocolServerToolCall::resultReady);
    tool.call(&call);
    QCOMPARE(tool.mCallCount, 1);
    QVERIFY(call.isFinished());
    QCOMPARE(resultSpy.count(), 1);
}

#include "moc_mcpprotocolserverconfirmationtooltest.cpp"
