// SPDX-FileCopyrightText: 2023 Loren Burkholder <computersemiexpert@outlook.com>
// SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
// SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>
// Based on Alpaka code and OllamaCommonReply
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lmstudioreply.h"
#include "autogeneratetext_lmstudio_debug.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

using namespace Qt::StringLiterals;

LMStudioReply::LMStudioReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateReply{netReply, requestType, parent}
{
    connect(mReply, &QNetworkReply::errorOccurred, mReply, [](QNetworkReply::NetworkError e) {
        qCDebug(AUTOGENERATETEXT_LMSTUDIO_LOG) << "Reply HTTP error:" << e;
    });
    connect(mReply, &QNetworkReply::finished, mReply, [this] {
        qCDebug(AUTOGENERATETEXT_LMSTUDIO_LOG) << "Reply response finished";
        Q_EMIT finished();
    });
    connect(mReply, &QNetworkReply::downloadProgress, mReply, [this](qint64 received, qint64 /*total*/) {
        QByteArray data = mReply->read(received - mReceivedSize);
        data.replace("data: ", "");
        mIncompleteTokens += data;
        qCDebug(AUTOGENERATETEXT_LMSTUDIO_LOG) << " data " << mIncompleteTokens;
        mReceivedSize = received;

        switch (mRequestType) {
        case RequestTypes::DownloadModel: {
            break;
        }
        case RequestTypes::DeleteModel:
        case RequestTypes::CreateModel:
        case RequestTypes::Unknown:
            break;
        case RequestTypes::ShowModelInfo:
            mTokens.append(QJsonDocument::fromJson(mIncompleteTokens));
            break;
        case RequestTypes::StreamingChat: {
            auto completeTokens = mIncompleteTokens.split('\n');
            if (completeTokens.size() <= 1) {
                return;
            }
            // qDebug() << " completeTokens " << completeTokens;
            mIncompleteTokens = completeTokens.last();
            completeTokens.removeLast();

            mTokens.reserve(completeTokens.count());
            for (const auto &tok : std::as_const(completeTokens)) {
                if (tok.isEmpty()) {
                    continue;
                }
                // Message send by server => it's not a json element
                if (tok != "[DONE]") {
                    mTokens.append(QJsonDocument::fromJson(tok));
                }
            }
            break;
        }
        case RequestTypes::StreamingGenerate:
            break;
        }

        Q_EMIT contentAdded();
    });
}

LMStudioReply::~LMStudioReply() = default;

TextAutoGenerateText::TextAutoGenerateReply::Response LMStudioReply::readResponse() const
{
    TextAutoGenerateText::TextAutoGenerateReply::Response ret;
    switch (mRequestType) {
    case RequestTypes::DownloadModel:
    case RequestTypes::DeleteModel:
    case RequestTypes::CreateModel:
    case RequestTypes::Unknown:
    case RequestTypes::ShowModelInfo:
    case RequestTypes::StreamingGenerate:
        break;
    case RequestTypes::StreamingChat:
        // qDebug() << " mTokens " << mTokens;
        for (const auto &tok : mTokens) {
            // qDebug() << " tok" << tok;
            const QJsonArray choicesArray = tok["choices"_L1].toArray();
            // qDebug() << " choicesArray " << choicesArray;
            if (!choicesArray.isEmpty()) {
                const QJsonObject firstObject = choicesArray.at(0).toObject();
                const QJsonObject deltaObject = firstObject["delta"_L1].toObject();
                if (deltaObject.contains(u"content"_s)) {
                    ret.response += deltaObject["content"_L1].toString();
                }
                if (deltaObject.contains(u"tool_calls"_s)) {
                    const QJsonArray toolCallResponse = deltaObject["tool_calls"_L1].toArray();
                    qDebug() << " tool_calls: " << toolCallResponse;
                    const QList<TextAutoGenerateReply::ToolCallArgumentInfo> infos = parseToolCallsOpenAI(toolCallResponse);
                    ret.info.append(infos);
                }
            }
        }
        if (!mTokens.isEmpty()) {
            const auto finalResponse = mTokens.constLast();
            // TODO it seems that it doesn't return completion token and others !
            // We need to investigate it.
            // TODO use "usage" in openAI api
            // "usage":{"completion_tokens":478,"prompt_tokens":46,"prompt_tokens_details":{"cached_tokens":0},"total_tokens":524}}

            TextAutoGenerateText::TextAutoGenerateTextReplyInfo replyInfo;
            replyInfo.replyType = TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::OpenAI;
            const auto usage = finalResponse["usage"_L1].toObject();
            if (!usage.isEmpty()) {
                replyInfo.tokenCount = usage["total_tokens"_L1].toVariant().toULongLong();
                replyInfo.completionTokens = usage["completion_tokens"_L1].toVariant().toULongLong();
                replyInfo.promptTokens = usage["prompt_tokens"_L1].toVariant().toULongLong();
                ret.replyInfo = replyInfo;
            }

            // "{\"id\":\"b72cdf33d58440838134fc042e98521b\",\"object\":\"chat.completion.chunk\",\"created\":1759381277,\"model\":\"magistral-small-2509\",\"choices\":[{\"index\":0,\"delta\":{\"tool_calls\":[{\"id\":\"QNfTI1iiJ\",\"function\":{\"name\":\"current_date_time_tool\",\"arguments\":\"{\\\"currentdatetime\\\":
            // \\\"time\\\"}\"},\"index\":0}]},\"finish_reason\":\"tool_calls\"}],\"usage\":{\"prompt_tokens\":275,\"total_tokens\":324,\"completion_tokens\":49}}\n\n[DONE]\n\n
        }
        break;
    }
    return ret;
}

#include "moc_lmstudioreply.cpp"
