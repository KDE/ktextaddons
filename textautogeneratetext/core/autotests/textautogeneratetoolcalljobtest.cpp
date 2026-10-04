/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolcalljobtest.h"
#include "core/tools/textautogeneratetexttoolinternal.h"
#include "core/tools/textautogeneratetexttoolinternalinterface.h"
#include "core/tools/textautogeneratetexttoolinternaljob.h"
#include "core/tools/textautogeneratetoolcalljob.h"
#include <QSignalSpy>
#include <QTest>
#include <QTimer>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateToolCallJobTest)

namespace
{
// Returns tool name and its arguments, asynchronously or not
class EchoToolJob : public TextAutoGenerateText::TextAutoGenerateTextToolInternalJob
{
public:
    EchoToolJob(const QByteArray &name, bool async, QObject *parent)
        : TextAutoGenerateText::TextAutoGenerateTextToolInternalJob(parent)
        , mName(name)
        , mAsync(async)
    {
    }

    void start() override
    {
        auto emitResult = [this]() {
            QString content = QString::fromLatin1(mName);
            for (const auto &arg : toolArguments()) {
                content += u' ' + arg.value;
            }
            Q_EMIT finished(
                {.content = content, .messageUuid = messageUuid(), .chatId = chatId(), .toolIdentifier = toolIdentifier(), .attachementInfoList = {}});
            deleteLater();
        };
        if (mAsync) {
            QTimer::singleShot(0, this, emitResult);
        } else {
            emitResult();
        }
    }

    [[nodiscard]] QByteArray toolName() const override
    {
        return mName;
    }

private:
    const QByteArray mName;
    const bool mAsync;
};

class EchoToolInterface : public TextAutoGenerateText::TextAutoGenerateTextToolInternalInterface
{
public:
    EchoToolInterface()
    {
        QList<TextAutoGenerateText::TextAutoGenerateTextToolInternal> tools;
        for (const auto &name : {"sync_tool"_ba, "async_tool"_ba}) {
            TextAutoGenerateText::TextAutoGenerateTextToolInternal tool;
            tool.setToolNameId(name);
            tools.append(tool);
        }
        setTools(tools);
    }

    TextAutoGenerateText::TextAutoGenerateTextToolInternalJob *callTool(const QByteArray &toolName) override
    {
        return new EchoToolJob(toolName, toolName == "async_tool"_ba, this);
    }
};

TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo toolCall(const QByteArray &name, const QString &value = {})
{
    TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo info;
    info.toolName = name;
    info.id = "id_" + name;
    if (!value.isEmpty()) {
        info.toolCallArgument = {{.keyTool = u"arg"_s, .value = value}};
    }
    return info;
}
}

TextAutoGenerateToolCallJobTest::TextAutoGenerateToolCallJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateToolCallJobTest::shouldNotStartWithoutInfo()
{
    const TextAutoGenerateText::TextAutoGenerateToolCallJob job("chat"_ba, "uuid"_ba, {});
    QVERIFY(!job.canStart());
}

void TextAutoGenerateToolCallJobTest::shouldCallSeveralTools()
{
    EchoToolInterface interface;
    // Synchronous tool first: result must wait for asynchronous tool
    auto job =
        new TextAutoGenerateText::TextAutoGenerateToolCallJob("chat"_ba, "uuid"_ba, {toolCall("sync_tool"_ba, u"a"_s), toolCall("async_tool"_ba, u"b"_s)});
    job->setTextAutoGenerateTextToolInternalInterface(&interface);
    QSignalSpy finishedSpy(job, &TextAutoGenerateText::TextAutoGenerateToolCallJob::finished);
    QSignalSpy toolResultsSpy(job, &TextAutoGenerateText::TextAutoGenerateToolCallJob::toolResults);
    job->start();
    QTRY_COMPARE(finishedSpy.count(), 1);
    const auto info = finishedSpy.at(0).at(0).value<TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo>();
    QCOMPARE(info.content, u"sync_tool a\nasync_tool b"_s);
    // Result of each tool, in order of tool calls
    QCOMPARE(toolResultsSpy.count(), 1);
    using ToolResults = QList<QPair<QByteArray, QString>>;
    const auto results = toolResultsSpy.at(0).at(0).value<ToolResults>();
    const ToolResults expected{{"id_sync_tool"_ba, u"sync_tool a"_s}, {"id_async_tool"_ba, u"async_tool b"_s}};
    QCOMPARE(results, expected);
    QCOMPARE(info.chatId, "chat"_ba);
    QCOMPARE(info.messageUuid, "uuid"_ba);
}

void TextAutoGenerateToolCallJobTest::shouldReportUnknownTool()
{
    EchoToolInterface interface;
    auto job = new TextAutoGenerateText::TextAutoGenerateToolCallJob("chat"_ba, "uuid"_ba, {toolCall("unknown_tool"_ba), toolCall("async_tool"_ba, u"b"_s)});
    job->setTextAutoGenerateTextToolInternalInterface(&interface);
    QSignalSpy finishedSpy(job, &TextAutoGenerateText::TextAutoGenerateToolCallJob::finished);
    job->start();
    // Unknown tool must not stop other tools
    QTRY_COMPARE(finishedSpy.count(), 1);
    QTest::qWait(50);
    QCOMPARE(finishedSpy.count(), 1);
    const auto info = finishedSpy.at(0).at(0).value<TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo>();
    QVERIFY(info.content.contains(u"unknown_tool"_s));
    QVERIFY(info.content.contains(u"async_tool b"_s));
    QCOMPARE(info.chatId, "chat"_ba);
    QCOMPARE(info.messageUuid, "uuid"_ba);

    // Only unknown tool
    auto unknownJob = new TextAutoGenerateText::TextAutoGenerateToolCallJob("chat"_ba, "uuid"_ba, {toolCall("unknown_tool"_ba)});
    QSignalSpy unknownSpy(unknownJob, &TextAutoGenerateText::TextAutoGenerateToolCallJob::finished);
    unknownJob->start();
    QCOMPARE(unknownSpy.count(), 1);
    QCOMPARE(unknownSpy.at(0).at(0).value<TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo>().chatId, "chat"_ba);
}

#include "moc_textautogeneratetoolcalljobtest.cpp"
