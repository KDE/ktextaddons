/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkreply.h"
#include "autogeneratetext_genericnetwork_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

using namespace Qt::Literals::StringLiterals;
GenericNetworkReply::GenericNetworkReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateReply{netReply, requestType, parent}
{
    connect(mReply, &QNetworkReply::errorOccurred, mReply, [](QNetworkReply::NetworkError e) {
        qCDebug(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "GenericNetworkReply HTTP error:" << e;
    });
    connect(mReply, &QNetworkReply::finished, mReply, [this] {
        qCDebug(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "GenericNetworkReply response finished";
        Q_EMIT finished();
    });
    connect(mReply, &QNetworkReply::downloadProgress, mReply, [this](qint64 received, qint64 /*total*/) {
        QByteArray data = mReply->read(received - mReceivedSize);
        data.replace("data: ", "");
        mIncompleteTokens += data;
        qCDebug(AUTOGENERATETEXT_GENERICNETWORK_LOG) << " data " << mIncompleteTokens;
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

            mTokens.reserve(mTokens.count() + completeTokens.count());
            for (const auto &tok : std::as_const(completeTokens)) {
                if (tok.isEmpty()) {
                    continue;
                }
                // Message send by server => it's not a json element
                if (tok != "[DONE]") {
                    const QJsonDocument doc = QJsonDocument::fromJson(tok);
                    mTokens.append(doc);
                    accumulateStreamedToken(doc);
                }
            }
            break;
        }
        case RequestTypes::StreamingGenerate:
            break;
        case RequestTypes::StreamingResponses:
            // TODO
            break;
        }

        Q_EMIT contentAdded();
    });
}

GenericNetworkReply::~GenericNetworkReply() = default;

TextAutoGenerateText::TextAutoGenerateReply::Response GenericNetworkReply::readResponse() const
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
    case RequestTypes::StreamingResponses:
        // TODO
        break;
    case RequestTypes::StreamingChat:
        // Already folded in by accumulateStreamedToken() as the tokens arrived.
        return mStreamedResponse;
    }
    return ret;
}

void GenericNetworkReply::accumulateStreamedToken(const QJsonDocument &tok)
{
    if (mRequestType != RequestTypes::StreamingChat) {
        return;
    }
    // qDebug() << " tok" << tok;
    if (const QJsonArray choicesArray = tok["choices"_L1].toArray(); !choicesArray.isEmpty()) {
        const QJsonObject firstObject = choicesArray.at(0).toObject();
        const QJsonObject deltaObject = firstObject["delta"_L1].toObject();
        if (const QJsonValue contentValue = deltaObject.value("content"_L1); !contentValue.isUndefined()) {
            mStreamedResponse.response += contentValue.toString();
        }
        if (const QJsonValue toolCallsValue = deltaObject.value("tool_calls"_L1); !toolCallsValue.isUndefined()) {
            const QJsonArray toolCallResponse = toolCallsValue.toArray();
            qDebug() << " tool_calls: " << toolCallResponse;
            mStreamedResponse.info.append(parseToolCallsOpenAI(toolCallResponse));
        }
    }
    // TODO use "usage" in openAI api
    // "usage":{"completion_tokens":478,"prompt_tokens":46,"prompt_tokens_details":{"cached_tokens":0},"total_tokens":524}}
    // Only the last token carries the usage, so each token simply overwrites it.
    TextAutoGenerateText::TextAutoGenerateTextReplyInfo replyInfo;
    replyInfo.replyType = TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::OpenAI;
    const auto usage = tok["usage"_L1].toObject();
    replyInfo.tokenCount = usage["total_tokens"_L1].toVariant().toULongLong();
    replyInfo.completionTokens = usage["completion_tokens"_L1].toVariant().toULongLong();
    replyInfo.promptTokens = usage["prompt_tokens"_L1].toVariant().toULongLong();
    mStreamedResponse.replyInfo = replyInfo;
}

#include "moc_genericnetworkreply.cpp"
