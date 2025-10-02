/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
            break;
        case RequestTypes::CreateModel:
            break;
        case RequestTypes::Unknown:
            break;
        case RequestTypes::Show:
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
                mTokens.append(QJsonDocument::fromJson(tok));
            }
            break;
        }
        case RequestTypes::StreamingGenerate:
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
    case RequestTypes::Show:
    case RequestTypes::StreamingGenerate:
        break;
    case RequestTypes::StreamingChat:
        // qDebug() << " mTokens " << mTokens;
        for (const auto &tok : mTokens) {
            const QJsonArray choicesArray = tok["choices"_L1].toArray();
            if (!choicesArray.isEmpty()) {
                ret.response += choicesArray.at(0).toObject()["delta"_L1]["content"_L1].toString();
            }
            if (tok["message"_L1].toObject().contains("tool_calls"_L1)) {
                qDebug() << " tool_calls: " << tok["message"_L1]["tool_calls"_L1];
            }
        }
        // "{\"id\":\"b72cdf33d58440838134fc042e98521b\",\"object\":\"chat.completion.chunk\",\"created\":1759381277,\"model\":\"magistral-small-2509\",\"choices\":[{\"index\":0,\"delta\":{\"tool_calls\":[{\"id\":\"QNfTI1iiJ\",\"function\":{\"name\":\"current_date_time_tool\",\"arguments\":\"{\\\"currentdatetime\\\":
        // \\\"time\\\"}\"},\"index\":0}]},\"finish_reason\":\"tool_calls\"}],\"usage\":{\"prompt_tokens\":275,\"total_tokens\":324,\"completion_tokens\":49}}\n\n[DONE]\n\n
        break;
    }
    return ret;
}

#include "moc_genericnetworkreply.cpp"
