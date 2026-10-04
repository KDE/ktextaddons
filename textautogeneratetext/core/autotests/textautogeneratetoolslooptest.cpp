/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolslooptest.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstance.h"
#include "core/textautogeneratetextplugin.h"
#include "core/tools/textautogeneratetexttoolinternal.h"
#include "core/tools/textautogeneratetexttoolinternalinterface.h"
#include "core/tools/textautogeneratetexttoolinternaljob.h"
#include <QJsonObject>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateToolsLoopTest)

namespace
{
// Returns its arguments
class EchoToolJob : public TextAutoGenerateText::TextAutoGenerateTextToolInternalJob
{
public:
    using TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::TextAutoGenerateTextToolInternalJob;
    void start() override
    {
        QString content = u"echo"_s;
        for (const auto &arg : toolArguments()) {
            content += u' ' + arg.value;
        }
        Q_EMIT finished({.content = content, .messageUuid = messageUuid(), .chatId = chatId(), .toolIdentifier = toolIdentifier(), .attachementInfoList = {}});
        deleteLater();
    }
    [[nodiscard]] QByteArray toolName() const override
    {
        return "echo_tool"_ba;
    }
};

class EchoToolInterface : public TextAutoGenerateText::TextAutoGenerateTextToolInternalInterface
{
public:
    EchoToolInterface()
    {
        TextAutoGenerateText::TextAutoGenerateTextToolInternal tool;
        tool.setToolNameId("echo_tool"_ba);
        setTools({tool});
    }
    TextAutoGenerateText::TextAutoGenerateTextToolInternalJob *callTool(const QByteArray &) override
    {
        return new EchoToolJob(this);
    }
};

// LLM which asks to call a tool, then answers when it gets tool result
class FakeLlmPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
public:
    using TextAutoGenerateText::TextAutoGenerateTextPlugin::TextAutoGenerateTextPlugin;

    QList<SendToAssistantInfo> requests;
    bool alwaysCallTool = false;
    TextAutoGenerateText::TextAutoGenerateMessage::ToolCallFormat format = TextAutoGenerateText::TextAutoGenerateMessage::ToolCallFormat::OpenAI;

    void showConfigureDialog(QWidget *) override
    {
    }
    [[nodiscard]] QString translatedPluginName() const override
    {
        return u"fake"_s;
    }
    [[nodiscard]] QString engineName() const override
    {
        return u"fake"_s;
    }
    [[nodiscard]] QString currentModel() const override
    {
        return u"model"_s;
    }
    void setCurrentModel(const QString &) override
    {
    }
    void askToAssistant(const QString &) override
    {
    }
    [[nodiscard]] QString displayName() const override
    {
        return u"fake"_s;
    }
    void setDisplayName(const QString &) override
    {
    }
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType engineType() const override
    {
        return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local;
    }
    [[nodiscard]] bool hasVisionSupport() const override
    {
        return false;
    }
    [[nodiscard]] bool hasToolsSupport() const override
    {
        return true;
    }
    [[nodiscard]] bool hasOcrSupport() const override
    {
        return false;
    }
    [[nodiscard]] bool hasAudioSupport() const override
    {
        return false;
    }
    [[nodiscard]] bool hasThinkSupport() const override
    {
        return false;
    }
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateMessage::ToolCallFormat toolCallFormat() const override
    {
        return format;
    }

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override
    {
        requests.append(info);
        if (info.toolTurn == 0 || alwaysCallTool) {
            TextAutoGenerateText::TextAutoGenerateReply::Response response;
            response.response = u"Let me check"_s;
            TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo toolCall;
            toolCall.toolName = "echo_tool"_ba;
            toolCall.arguments = QJsonObject{{"city"_L1, u"Paris"_s}};
            toolCall.toolCallArgument = {{.keyTool = u"city"_s, .value = u"Paris"_s}};
            response.info = {toolCall};
            processToolCalls(info, response);
            return;
        }
        TextAutoGenerateText::TextAutoGenerateReply::Response response;
        response.response = u"Final answer"_s;
        manager()->replaceContent(info.chatId, info.messageUuid, response, {});
        manager()->changeInProgress(info.chatId, info.messageUuid, false);
    }
};

TextAutoGenerateText::TextAutoGenerateMessage lastMessage(TextAutoGenerateText::TextAutoGenerateManager &manager, const QByteArray &chatId)
{
    return manager.messagesModelFromChatId(chatId)->messages().constLast();
}
}

TextAutoGenerateToolsLoopTest::TextAutoGenerateToolsLoopTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateToolsLoopTest::shouldSendToolResultsToLLM()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    EchoToolInterface toolInterface;
    manager.setTextAutoGenerateTextToolInternalInterface(&toolInterface);
    const QByteArray chatId = manager.createEphemeralChat();
    TextAutoGenerateText::TextAutoGenerateTextInstance instance;
    FakeLlmPlugin plugin(&manager, &instance);
    plugin.setReady(true);
    plugin.sendMessage({.message = u"Weather?"_s, .messageUuid = {}, .chatId = chatId, .tools = {}, .attachmentInfoList = {}});

    QTRY_COMPARE(plugin.requests.count(), 2);
    QCOMPARE(plugin.requests.at(1).toolTurn, 1);
    // Messages sent with tool result: system prompt, user question, tool call, tool result
    const QJsonArray messages = plugin.requests.at(1).messagesArray;
    QCOMPARE(messages.count(), 4);
    QCOMPARE(messages.at(0).toObject().value("role"_L1).toString(), u"system"_s);
    QCOMPARE(messages.at(1).toObject().value("role"_L1).toString(), u"user"_s);
    const QJsonObject assistant = messages.at(2).toObject();
    QCOMPARE(assistant.value("role"_L1).toString(), u"assistant"_s);
    QCOMPARE(assistant.value("content"_L1).toString(), u"Let me check"_s);
    const QJsonObject toolCall = assistant.value("tool_calls"_L1).toArray().at(0).toObject();
    // Id generated when LLM doesn't send it
    QCOMPARE(toolCall.value("id"_L1).toString(), u"call_0_0"_s);
    QCOMPARE(toolCall.value("function"_L1).toObject().value("name"_L1).toString(), u"echo_tool"_s);
    QCOMPARE(messages.at(3).toObject(), QJsonObject({{"role"_L1, u"tool"_s}, {"tool_call_id"_L1, u"call_0_0"_s}, {"content"_L1, u"echo Paris"_s}}));

    // Final answer is shown, tool calls are kept for next messages
    QTRY_VERIFY(!lastMessage(manager, chatId).inProgress());
    const auto answer = lastMessage(manager, chatId);
    QCOMPARE(answer.content(), u"Final answer"_s);
    QCOMPARE(answer.toolExchange().count(), 2);
    const auto history = manager.messagesModelFromChatId(chatId)->convertToOllamaChat(true, true);
    QCOMPARE(history.count(), 4);
    QCOMPARE(history.constLast().value("content"_L1).toString(), u"Final answer"_s);
}

void TextAutoGenerateToolsLoopTest::shouldSendToolResultsInOllamaFormat()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    EchoToolInterface toolInterface;
    manager.setTextAutoGenerateTextToolInternalInterface(&toolInterface);
    const QByteArray chatId = manager.createEphemeralChat();
    TextAutoGenerateText::TextAutoGenerateTextInstance instance;
    FakeLlmPlugin plugin(&manager, &instance);
    plugin.format = TextAutoGenerateText::TextAutoGenerateMessage::ToolCallFormat::Ollama;
    plugin.setReady(true);
    plugin.sendMessage({.message = u"Weather?"_s, .messageUuid = {}, .chatId = chatId, .tools = {}, .attachmentInfoList = {}});

    QTRY_COMPARE(plugin.requests.count(), 2);
    const QJsonArray messages = plugin.requests.at(1).messagesArray;
    QCOMPARE(messages.count(), 4);
    const QJsonObject function = messages.at(2).toObject().value("tool_calls"_L1).toArray().at(0).toObject().value("function"_L1).toObject();
    QCOMPARE(function.value("arguments"_L1).toObject(), QJsonObject({{"city"_L1, u"Paris"_s}}));
    QCOMPARE(messages.at(3).toObject(), QJsonObject({{"role"_L1, u"tool"_s}, {"tool_name"_L1, u"echo_tool"_s}, {"content"_L1, u"echo Paris"_s}}));
}

void TextAutoGenerateToolsLoopTest::shouldStopAfterTooManyToolCalls()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    EchoToolInterface toolInterface;
    manager.setTextAutoGenerateTextToolInternalInterface(&toolInterface);
    const QByteArray chatId = manager.createEphemeralChat();
    TextAutoGenerateText::TextAutoGenerateTextInstance instance;
    FakeLlmPlugin plugin(&manager, &instance);
    plugin.alwaysCallTool = true;
    plugin.setReady(true);
    plugin.sendMessage({.message = u"Weather?"_s, .messageUuid = {}, .chatId = chatId, .tools = {}, .attachmentInfoList = {}});

    QTRY_VERIFY(!lastMessage(manager, chatId).inProgress());
    // First request + 10 requests with tool results
    QCOMPARE(plugin.requests.count(), 11);
    // Result of last tool is shown
    QCOMPARE(lastMessage(manager, chatId).content(), u"echo Paris"_s);
}

#include "moc_textautogeneratetoolslooptest.cpp"
