/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcpsamplingjob.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageResult>
#include <optional>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role;

namespace
{
// Text of content, nullopt when content isn't only text (image, audio, tool use…)
std::optional<QString> contentText(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::CreateMessageResultContent &content)
{
    if (const auto text = std::get_if<TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent>(&content)) {
        return text->text();
    }
    if (const auto blocks = std::get_if<QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::SamplingMessageContentBlock>>(&content)) {
        QStringList texts;
        for (const auto &block : *blocks) {
            const auto text = std::get_if<TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent>(&block);
            if (!text) {
                return std::nullopt;
            }
            texts.append(text->text());
        }
        return texts.join(u'\n');
    }
    return std::nullopt;
}
}

TextAutoGenerateMcpSamplingJob::TextAutoGenerateMcpSamplingJob(TextAutoGenerateTextPlugin *plugin, QObject *parent)
    : QObject{parent}
    , mPlugin(plugin)
{
}

TextAutoGenerateMcpSamplingJob::~TextAutoGenerateMcpSamplingJob()
{
    // Abort request when job is deleted before end
    delete mReply;
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest TextAutoGenerateMcpSamplingJob::request() const
{
    return mRequest;
}

void TextAutoGenerateMcpSamplingJob::setRequest(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &newRequest)
{
    mRequest = newRequest;
}

QJsonArray TextAutoGenerateMcpSamplingJob::convertMessages(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams &params,
                                                           bool systemMessageSupport)
{
    QJsonArray array;
    QString systemPrompt = params.systemPrompt().value_or(QString());
    if (systemMessageSupport && !systemPrompt.isEmpty()) {
        array.append(QJsonObject{{"role"_L1, u"system"_s}, {"content"_L1, systemPrompt}});
        systemPrompt.clear();
    }
    const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage> messages = params.messages();
    for (const auto &message : messages) {
        const std::optional<QString> text = contentText(message.content());
        if (!text.has_value()) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Unsupported content in sampling request";
            return {};
        }
        QString content = *text;
        if (!systemPrompt.isEmpty()) {
            content = systemPrompt + u"\n\n"_s + content;
            systemPrompt.clear();
        }
        const QString role = message.role() == Role::Assistant ? u"assistant"_s : u"user"_s;
        array.append(QJsonObject{{"role"_L1, role}, {"content"_L1, content}});
    }
    if (messages.isEmpty()) {
        return {};
    }
    return array;
}

void TextAutoGenerateMcpSamplingJob::start()
{
    if (!mPlugin || !mPlugin->ready()) {
        emitFailed(i18n("No LLM available."));
        return;
    }
    const QJsonArray messages = convertMessages(mRequest.params(), mPlugin->hasSystemMessageSupport());
    if (messages.isEmpty()) {
        emitFailed(i18n("Sampling request contains unsupported content."));
        return;
    }
    mModel = mPlugin->currentModel();
    TextAutoGenerateTextRequest req;
    req.setModel(mModel);
    req.setMessages(messages);
    mReply = mPlugin->chatCompletion(req);
    if (!mReply) {
        emitFailed(i18n("LLM doesn't support sampling requests."));
        return;
    }
    connect(mReply, &TextAutoGenerateReply::errorOccurred, this, [this](QNetworkReply::NetworkError, const QString &errorString) {
        mErrorString = errorString;
    });
    connect(mReply, &TextAutoGenerateReply::finished, this, &TextAutoGenerateMcpSamplingJob::slotReplyFinished);
}

void TextAutoGenerateMcpSamplingJob::slotReplyFinished()
{
    const QString text = mReply->readResponse().response;
    mReply->deleteLater();
    mReply = nullptr;
    if (!mErrorString.isEmpty() || text.isEmpty()) {
        emitFailed(mErrorString.isEmpty() ? i18n("LLM returned an empty answer.") : mErrorString);
        return;
    }
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent content;
    content.setText(text);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult result;
    result.setContent(content);
    result.setModel(mModel);
    result.setRole(Role::Assistant);
    result.setStopReason(u"endTurn"_s);
    Q_EMIT finished(result);
    deleteLater();
}

void TextAutoGenerateMcpSamplingJob::emitFailed(const QString &errorString)
{
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Sampling request failed:" << errorString;
    Q_EMIT failed(errorString);
    deleteLater();
}

#include "moc_textautogeneratemcpsamplingjob.cpp"
