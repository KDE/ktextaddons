/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcpsamplingjobtest.h"
#include "core/mcp/textautogeneratemcpsamplingjob.h"
#include "core/textautogeneratetextplugin.h"
#include <QJsonObject>
#include <QPointer>
#include <QSignalSpy>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageResult>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
using TextAutoGenerateText::TextAutoGenerateMcpSamplingJob;
QTEST_GUILESS_MAIN(TextAutoGenerateMcpSamplingJobTest)

namespace
{
class FakeReply : public TextAutoGenerateText::TextAutoGenerateReply
{
public:
    FakeReply()
        : TextAutoGenerateText::TextAutoGenerateReply(nullptr, RequestTypes::StreamingChat)
    {
    }
    Response response;
    [[nodiscard]] Response readResponse() const override
    {
        return response;
    }
};

class FakeLlmPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
public:
    FakeLlmPlugin()
        : TextAutoGenerateText::TextAutoGenerateTextPlugin(nullptr, nullptr)
    {
        setReady(true);
    }

    bool supportSampling = true;
    bool systemMessageSupport = true;
    QList<TextAutoGenerateText::TextAutoGenerateTextRequest> requests;
    QPointer<FakeReply> reply;

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
        return false;
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
    [[nodiscard]] bool hasSystemMessageSupport() const override
    {
        return systemMessageSupport;
    }
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *chatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override
    {
        if (!supportSampling) {
            return TextAutoGenerateText::TextAutoGenerateTextPlugin::chatCompletion(request);
        }
        requests.append(request);
        reply = new FakeReply;
        return reply;
    }

protected:
    void sendToAssistant(const SendToAssistantInfo &) override
    {
    }
};

McpProtocolSamplingMessage textMessage(McpProtocolUtils::Role role, const QString &text)
{
    McpProtocolTextContent content;
    content.setText(text);
    McpProtocolSamplingMessage message;
    message.setRole(role);
    message.setContent(content);
    return message;
}

McpProtocolCreateMessageRequest createRequest()
{
    McpProtocolCreateMessageRequestParams params;
    params.setMessages({textMessage(McpProtocolUtils::Role::User, u"Hello"_s)});
    McpProtocolCreateMessageRequest request;
    request.setParams(params);
    return request;
}
}

TextAutoGenerateMcpSamplingJobTest::TextAutoGenerateMcpSamplingJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateMcpSamplingJobTest::shouldConvertMessages()
{
    McpProtocolCreateMessageRequestParams params;
    QVERIFY(TextAutoGenerateMcpSamplingJob::convertMessages(params, true).isEmpty());

    params.setSystemPrompt(u"Be short"_s);
    McpProtocolTextContent first;
    first.setText(u"Part 1"_s);
    McpProtocolTextContent second;
    second.setText(u"Part 2"_s);
    McpProtocolSamplingMessage blocks;
    blocks.setRole(McpProtocolUtils::Role::User);
    blocks.setContent(QList<McpProtocolUtils::SamplingMessageContentBlock>{first, second});
    params.setMessages({textMessage(McpProtocolUtils::Role::User, u"Hello"_s), textMessage(McpProtocolUtils::Role::Assistant, u"Hi"_s), blocks});

    const QJsonArray withSystem = TextAutoGenerateMcpSamplingJob::convertMessages(params, true);
    QCOMPARE(withSystem.count(), 4);
    QCOMPARE(withSystem.at(0).toObject(), (QJsonObject{{"role"_L1, u"system"_s}, {"content"_L1, u"Be short"_s}}));
    QCOMPARE(withSystem.at(1).toObject(), (QJsonObject{{"role"_L1, u"user"_s}, {"content"_L1, u"Hello"_s}}));
    QCOMPARE(withSystem.at(2).toObject(), (QJsonObject{{"role"_L1, u"assistant"_s}, {"content"_L1, u"Hi"_s}}));
    QCOMPARE(withSystem.at(3).toObject(), (QJsonObject{{"role"_L1, u"user"_s}, {"content"_L1, u"Part 1\nPart 2"_s}}));

    // System prompt is added to first message
    const QJsonArray withoutSystem = TextAutoGenerateMcpSamplingJob::convertMessages(params, false);
    QCOMPARE(withoutSystem.count(), 3);
    QCOMPARE(withoutSystem.at(0).toObject(), (QJsonObject{{"role"_L1, u"user"_s}, {"content"_L1, u"Be short\n\nHello"_s}}));
    QCOMPARE(withoutSystem.at(1).toObject().value("content"_L1).toString(), u"Hi"_s);
}

void TextAutoGenerateMcpSamplingJobTest::shouldNotConvertUnsupportedContent()
{
    McpProtocolSamplingMessage image;
    image.setRole(McpProtocolUtils::Role::User);
    image.setContent(McpProtocolImageContent());
    McpProtocolCreateMessageRequestParams params;
    params.setMessages({textMessage(McpProtocolUtils::Role::User, u"Hello"_s), image});
    QVERIFY(TextAutoGenerateMcpSamplingJob::convertMessages(params, true).isEmpty());

    McpProtocolTextContent text;
    text.setText(u"Look"_s);
    McpProtocolSamplingMessage blocks;
    blocks.setRole(McpProtocolUtils::Role::User);
    blocks.setContent(QList<McpProtocolUtils::SamplingMessageContentBlock>{text, McpProtocolImageContent()});
    params.setMessages({blocks});
    QVERIFY(TextAutoGenerateMcpSamplingJob::convertMessages(params, true).isEmpty());
}

void TextAutoGenerateMcpSamplingJobTest::shouldFailWithoutPlugin()
{
    auto job = new TextAutoGenerateMcpSamplingJob(nullptr);
    job->setRequest(createRequest());
    QSignalSpy failedSpy(job, &TextAutoGenerateMcpSamplingJob::failed);
    QSignalSpy finishedSpy(job, &TextAutoGenerateMcpSamplingJob::finished);
    job->start();
    QCOMPARE(failedSpy.count(), 1);
    QVERIFY(!failedSpy.at(0).at(0).toString().isEmpty());
    QCOMPARE(finishedSpy.count(), 0);
}

void TextAutoGenerateMcpSamplingJobTest::shouldFailWhenPluginDoesNotSupportIt()
{
    FakeLlmPlugin plugin;
    plugin.supportSampling = false;
    auto job = new TextAutoGenerateMcpSamplingJob(&plugin);
    job->setRequest(createRequest());
    QSignalSpy failedSpy(job, &TextAutoGenerateMcpSamplingJob::failed);
    job->start();
    QCOMPARE(failedSpy.count(), 1);
}

void TextAutoGenerateMcpSamplingJobTest::shouldReturnGeneratedMessage()
{
    FakeLlmPlugin plugin;
    auto job = new TextAutoGenerateMcpSamplingJob(&plugin);
    job->setRequest(createRequest());
    QSignalSpy finishedSpy(job, &TextAutoGenerateMcpSamplingJob::finished);
    QSignalSpy failedSpy(job, &TextAutoGenerateMcpSamplingJob::failed);
    job->start();
    QCOMPARE(plugin.requests.count(), 1);
    QCOMPARE(plugin.requests.at(0).model(), u"model"_s);
    QCOMPARE(plugin.requests.at(0).messages().count(), 1);
    QVERIFY(plugin.requests.at(0).tools().isEmpty());

    plugin.reply->response.response = u"Generated"_s;
    Q_EMIT plugin.reply->finished();
    QCOMPARE(failedSpy.count(), 0);
    QCOMPARE(finishedSpy.count(), 1);
    const auto result = finishedSpy.at(0).at(0).value<McpProtocolCreateMessageResult>();
    QCOMPARE(result.model(), u"model"_s);
    QCOMPARE(result.role(), McpProtocolUtils::Role::Assistant);
    QCOMPARE(result.stopReason(), u"endTurn"_s);
    QCOMPARE(std::get<McpProtocolTextContent>(result.content()).text(), u"Generated"_s);
    // Reply and job are deleted
    QTRY_VERIFY(!plugin.reply);
}

void TextAutoGenerateMcpSamplingJobTest::shouldFailWhenLlmFails()
{
    FakeLlmPlugin plugin;
    auto job = new TextAutoGenerateMcpSamplingJob(&plugin);
    job->setRequest(createRequest());
    QSignalSpy failedSpy(job, &TextAutoGenerateMcpSamplingJob::failed);
    job->start();
    QVERIFY(plugin.reply);
    Q_EMIT plugin.reply->errorOccurred(QNetworkReply::ConnectionRefusedError, u"Connection refused"_s);
    Q_EMIT plugin.reply->finished();
    QCOMPARE(failedSpy.count(), 1);
    QCOMPARE(failedSpy.at(0).at(0).toString(), u"Connection refused"_s);

    // Empty answer
    auto emptyJob = new TextAutoGenerateMcpSamplingJob(&plugin);
    emptyJob->setRequest(createRequest());
    QSignalSpy emptyFailedSpy(emptyJob, &TextAutoGenerateMcpSamplingJob::failed);
    emptyJob->start();
    Q_EMIT plugin.reply->finished();
    QCOMPARE(emptyFailedSpy.count(), 1);
}
