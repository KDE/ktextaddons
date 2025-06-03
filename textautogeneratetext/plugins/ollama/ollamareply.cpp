// SPDX-FileCopyrightText: 2023 Loren Burkholder <computersemiexpert@outlook.com>
// SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
// Based on Alpaka code
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ollamareply.h"
#include "autogeneratetext_ollama_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

using namespace Qt::StringLiterals;
using namespace Qt::Literals::StringLiterals;
OllamaReply::OllamaReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateReply{netReply, requestType, parent}
{
    connect(mReply, &QNetworkReply::finished, mReply, [this] {
        // Normally, we could assume that the tokens will never be empty once the request finishes, but it could be possible
        // that the request failed and we have no tokens to parse.
        if ((mRequestType == RequestTypes::StreamingGenerate || mRequestType == RequestTypes::StreamingChat) && !mTokens.empty()) {
            const auto finalResponse = mTokens.constLast();
            mContext.setContextData(finalResponse["context"_L1].toArray());
            mInfo.totalDuration = std::chrono::nanoseconds{finalResponse["total_duration"_L1].toVariant().toULongLong()};
            mInfo.loadDuration = std::chrono::nanoseconds{finalResponse["load_duration"_L1].toVariant().toULongLong()};
            mInfo.promptEvalTokenCount = finalResponse["prompt_eval_count"_L1].toVariant().toULongLong();
            mInfo.promptEvalDuration = std::chrono::nanoseconds{finalResponse["prompt_eval_duration"_L1].toVariant().toULongLong()};
            mInfo.tokenCount = finalResponse["eval_count"_L1].toVariant().toULongLong();
            mInfo.duration = std::chrono::nanoseconds{finalResponse["eval_duration"_L1].toVariant().toULongLong()};
        }
        qCDebug(AUTOGENERATETEXT_OLLAMA_LOG) << "Ollama response finished";
        Q_EMIT finished();
    });
    connect(mReply, &QNetworkReply::errorOccurred, mReply, [](QNetworkReply::NetworkError e) {
        qCDebug(AUTOGENERATETEXT_OLLAMA_LOG) << "Ollama HTTP error:" << e;
    });
    connect(mReply, &QNetworkReply::downloadProgress, mReply, [this](qint64 received, qint64 /*total*/) {
        const QByteArray data = mReply->read(received - mReceivedSize);
        mIncompleteTokens += data;
        mReceivedSize = received;

        switch (mRequestType) {
        case RequestTypes::DownloadModel: {
            const auto completeTokens = mIncompleteTokens.split('\n');
            if (completeTokens.isEmpty()) {
                return;
            }
            for (const QByteArray &ba : completeTokens) {
                if (!ba.isEmpty()) {
                    Q_EMIT downloadInProgress(parseDownLoadInfo(QJsonDocument::fromJson(ba)));
                }
            }
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
            mIncompleteTokens = completeTokens.last();
            completeTokens.removeLast();

            mTokens.reserve(completeTokens.count());
            for (const auto &tok : std::as_const(completeTokens)) {
                mTokens.append(QJsonDocument::fromJson(tok));
            }
            break;
        }
        case RequestTypes::StreamingGenerate:
            auto completeTokens = mIncompleteTokens.split('\n');
            if (completeTokens.size() <= 1) {
                return;
            }
            mIncompleteTokens = completeTokens.last();
            completeTokens.removeLast();

            mTokens.reserve(completeTokens.count());
            for (const auto &tok : std::as_const(completeTokens)) {
                mTokens.append(QJsonDocument::fromJson(tok));
            }
            break;
        }

        Q_EMIT contentAdded();
    });
}

OllamaReply::~OllamaReply() = default;

QString OllamaReply::readResponse() const
{
    QString ret;
    switch (mRequestType) {
    case RequestTypes::DownloadModel:
    case RequestTypes::DeleteModel:
    case RequestTypes::CreateModel:
    case RequestTypes::Unknown:
        break;
    case RequestTypes::StreamingChat:
        for (const auto &tok : mTokens) {
            ret += tok["message"_L1]["content"_L1].toString();
        }
        break;
    case RequestTypes::Show:
        // TODO
        break;
    case RequestTypes::StreamingGenerate:
        for (const auto &tok : mTokens) {
            ret += tok["response"_L1].toString();
        }
    }
    return ret;
}

TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo OllamaReply::parseDownLoadInfo(const QJsonDocument &doc) const
{
    TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo info;
    const QJsonObject obj = doc.object();
    info.completed = obj["completed"_L1].toInteger(0);
    info.total = obj["total"_L1].toInteger(0);
    info.status = obj["status"_L1].toString();
    return info;
}

#include "moc_ollamareply.cpp"
