// SPDX-FileCopyrightText: 2023 Loren Burkholder <computersemiexpert@outlook.com>
// SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// SPDX-FileCopyrightText: SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
// Based on Alpaka code
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ollamareply.h"
#include "autogeneratetext_ollama_debug.h"
#include <QJsonArray>
#include <QNetworkReply>

using namespace Qt::StringLiterals;

OllamaReply::OllamaReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : QObject{parent}
    , mReply{netReply}
    , mRequestType{requestType}
{
    connect(mReply, &QNetworkReply::finished, mReply, [this] {
        // Normally, we could assume that the tokens will never be empty once the request finishes, but it could be possible
        // that the request failed and we have no tokens to parse.
        if (mRequestType == RequestTypes::StreamingGenerate && !mTokens.empty()) {
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
        mFinished = true;
        Q_EMIT finished();
    });
    connect(mReply, &QNetworkReply::errorOccurred, mReply, [](QNetworkReply::NetworkError e) {
        qCDebug(AUTOGENERATETEXT_OLLAMA_LOG) << "Ollama HTTP error:" << e;
    });
    connect(mReply, &QNetworkReply::downloadProgress, mReply, [this](qint64 received, qint64 /*total*/) {
        mIncompleteTokens += mReply->read(received - mReceivedSize);
        mReceivedSize = received;

        switch (mRequestType) {
        case RequestTypes::Show:
            mTokens.append(QJsonDocument::fromJson(mIncompleteTokens));
            break;
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

const OllamaReply::RequestTypes &OllamaReply::requestType() const
{
    return mRequestType;
}

QString OllamaReply::readResponse() const
{
    QString ret;
    switch (mRequestType) {
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

const TextAutoGenerateText::TextAutoGenerateTextContext &OllamaReply::context() const
{
    return mContext;
}

const TextAutoGenerateText::TextAutoGenerateTextReplyInfo &OllamaReply::info() const
{
    return mInfo;
}

bool OllamaReply::isFinished() const
{
    return mFinished;
}

#include "moc_ollamareply.cpp"
