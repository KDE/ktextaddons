// SPDX-FileCopyrightText: 2023 Loren Burkholder <computersemiexpert@outlook.com>
// SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
// SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
// Based on Alpaka code
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ollamacommonreply.h"
#include "autogeneratetext_ollamacommon_debug.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

using namespace Qt::StringLiterals;
using namespace Qt::Literals::StringLiterals;
OllamaCommonReply::OllamaCommonReply(QNetworkReply *netReply, RequestTypes requestType, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateReply{netReply, requestType, parent}
{
    connect(mReply, &QNetworkReply::finished, mReply, [this] {
        // Normally, we could assume that the tokens will never be empty once the request finishes, but it could be possible
        // that the request failed and we have no tokens to parse.
        if ((mRequestType == RequestTypes::StreamingGenerate || mRequestType == RequestTypes::StreamingChat) && !mTokens.empty()) {
            const auto finalResponse = mTokens.constLast();
            mInfo.totalDuration = std::chrono::nanoseconds{finalResponse["total_duration"_L1].toVariant().toULongLong()};
            mInfo.loadDuration = std::chrono::nanoseconds{finalResponse["load_duration"_L1].toVariant().toULongLong()};
            mInfo.promptEvalTokenCount = finalResponse["prompt_eval_count"_L1].toVariant().toULongLong();
            mInfo.promptEvalDuration = std::chrono::nanoseconds{finalResponse["prompt_eval_duration"_L1].toVariant().toULongLong()};
            mInfo.tokenCount = finalResponse["eval_count"_L1].toVariant().toULongLong();
            mInfo.duration = std::chrono::nanoseconds{finalResponse["eval_duration"_L1].toVariant().toULongLong()};
        }
        qCDebug(AUTOGENERATETEXT_OLLAMACOMMON_LOG) << "Ollama response finished";
        if (mDownloadError) {
            return;
        }
        if (mReply->error() == QNetworkReply::NoError) {
            Q_EMIT finished();
        } else {
            Q_EMIT canceled();
        }
    });
    connect(mReply, &QNetworkReply::errorOccurred, mReply, [this](QNetworkReply::NetworkError e) {
        if (e == QNetworkReply::NetworkError::AuthenticationRequiredError) {
            // TODO need to authentication.
            qDebug() << " Need to authentication"; // cloud support
            Q_EMIT needOllamaLogin();
            Q_EMIT finished();
            return;
        }
        Q_EMIT errorOccurred(e);
        qDebug() << " DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" << e;
        qCDebug(AUTOGENERATETEXT_OLLAMACOMMON_LOG) << "Ollama HTTP error:" << e;
    });
    connect(mReply, &QNetworkReply::downloadProgress, mReply, [this](qint64 received, qint64 /*total*/) {
        const QByteArray data = mReply->read(received - mReceivedSize);
        if (data.isEmpty()) {
            return;
        }
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
                    const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo downloadInfo = parseDownLoadInfo(QJsonDocument::fromJson(ba));
                    if (downloadInfo.error.isEmpty()) {
                        Q_EMIT downloadInProgress(downloadInfo);
                    } else {
                        mDownloadError = true;
                        Q_EMIT downloadError(downloadInfo.error);
                    }
                }
            }
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
            mIncompleteTokens = completeTokens.last();
            completeTokens.removeLast();

            mTokens.reserve(completeTokens.count());
            for (const auto &tok : std::as_const(completeTokens)) {
                mTokens.append(QJsonDocument::fromJson(tok));
            }
            // TODO parse "tool_calls"
            // qDebug() << " mTokens " << mTokens;
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

OllamaCommonReply::~OllamaCommonReply()
{
    disconnect(mReply);
    mReply->abort();
    mReply->deleteLater();
}

TextAutoGenerateText::TextAutoGenerateReply::Response OllamaCommonReply::readResponse() const
{
    TextAutoGenerateText::TextAutoGenerateReply::Response ret;
    switch (mRequestType) {
    case RequestTypes::DownloadModel:
    case RequestTypes::DeleteModel:
    case RequestTypes::CreateModel:
    case RequestTypes::Unknown:
        break;
    case RequestTypes::StreamingChat:
        for (const auto &tok : mTokens) {
            const QJsonObject messageObj = tok["message"_L1].toObject();
            if (messageObj.contains("tool_calls"_L1)) {
                const QJsonArray array = tok["message"_L1]["tool_calls"_L1].toArray();
                // qDebug() << " tool_calls: " << array;
                const QList<TextAutoGenerateReply::ToolCallArgumentInfo> infos = parseToolCallsOllama(array);
                // qDebug() << " QList<TextAutoGenerateReply::ToolCallArgumentInfo> infos " << infos;
                ret.info.append(infos);
            }
            if (messageObj.contains("thinking"_L1)) {
                ret.response += messageObj["thinking"_L1].toString();
            } else {
                ret.response += messageObj["content"_L1].toString();
            }
        }
        break;
    case RequestTypes::ShowModelInfo:
        ret.response = generateModelInfo();
        break;
    case RequestTypes::StreamingGenerate:
        for (const auto &tok : mTokens) {
            ret.response += tok["response"_L1].toString();
        }
    }
    return ret;
}

QString OllamaCommonReply::generateModelInfo() const
{
    QString mardown;
    const QJsonDocument doc = mTokens.constFirst();
    QString capabilities;
    const QJsonArray array = doc["capabilities"_L1].toArray();
    for (const auto &val : array) {
        if (!capabilities.isEmpty()) {
            capabilities += u", "_s;
        }
        capabilities += val.toString();
    }
    if (!capabilities.isEmpty()) {
        mardown += u"## %1: \n```\n"_s.arg(i18n("Capabilities")) + capabilities + u"\n```\n\n\n"_s;
    }
    mardown += u"## %1: \n```\n"_s.arg(i18n("Template")) + doc["template"_L1].toString() + u"\n```\n\n\n"_s;
    mardown += u"## %1: \n```\n"_s.arg(i18n("Modelfile")) + doc["modelfile"_L1].toString() + u"\n```\n\n\n"_s;
    const QString parameters = doc["parameters"_L1].toString();
    if (!parameters.isEmpty()) {
        mardown += u"## %1: \n```\n"_s.arg(i18n("Parameters")) + doc["parameters"_L1].toString() + u"\n```\n\n\n"_s;
    }
    mardown +=
        u"## %1: \n```\n"_s.arg(i18n("Details")) + QString::fromLatin1(QJsonDocument::fromVariant(doc["details"_L1].toVariant()).toJson()) + u"\n```\n\n\n"_s;
    mardown += u"## %1: \n```\n"_s.arg(i18n("Model Info")) + QString::fromLatin1(QJsonDocument::fromVariant(doc["model_info"_L1].toVariant()).toJson())
        + u"\n```\n\n\n"_s;
    qDebug() << " mTokens " << doc;
    return mardown;
}

TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo OllamaCommonReply::parseDownLoadInfo(const QJsonDocument &doc) const
{
    const QJsonObject obj = doc.object();
    TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo info;
    info.completed = obj["completed"_L1].toInteger(0);
    info.total = obj["total"_L1].toInteger(0);
    info.status = obj["status"_L1].toString();
    info.error = obj["error"_L1].toString();
    // qDebug() << " info " << info;
    return info;
}

#include "moc_ollamacommonreply.cpp"
