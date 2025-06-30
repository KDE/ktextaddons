/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkreply.h"
#include "autogeneratetext_genericnetwork_debug.h"
#include <QJsonArray>
#include <QNetworkReply>
#include <qjsonobject.h>

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
        // qDebug() << " data " << mIncompleteTokens;
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

GenericNetworkReply::~GenericNetworkReply() = default;

QString GenericNetworkReply::readResponse() const
{
    QString ret;
    switch (mRequestType) {
    case RequestTypes::DownloadModel:
    case RequestTypes::DeleteModel:
    case RequestTypes::CreateModel:
    case RequestTypes::Unknown:
        break;
    case RequestTypes::StreamingChat:
        // qDebug() << " mTokens " << mTokens;
        for (const auto &tok : mTokens) {
            const QJsonArray a = tok["choices"_L1].toArray();
            ret += a.at(0).toObject()["delta"_L1]["content"_L1].toString();
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
    qDebug() << "ret " << ret;
    return ret;
}

#include "moc_genericnetworkreply.cpp"
