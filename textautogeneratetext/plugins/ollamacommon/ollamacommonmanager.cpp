/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "ollamacommonreply.h"
#include "ollamacommonutils.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
OllamaCommonManager::OllamaCommonManager(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
{
}

OllamaCommonManager::~OllamaCommonManager() = default;

bool OllamaCommonManager::hasVisionSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasToolsSupport([[maybe_unused]] const QString &modelName) const

{
    return false;
}

bool OllamaCommonManager::hasOcrSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasAudioSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasThinkSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

void OllamaCommonManager::showModelInfo(const QString &modelName)
{
    QUrl url = instanceUrl();
    url.setPath(OllamaCommonUtils::modelInfoPath());
    QNetworkRequest req{url};

    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    QJsonObject data;
    data["model"_L1] = modelName;

    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::ShowModelInfo,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply] {
        const auto readResponse = reply->readResponse();
        // qDebug() << " readResponse : " << readResponse;
        Q_EMIT finished(readResponse);
        Q_EMIT showModelInfoDone(readResponse.response);
    });
}

#include "moc_ollamacommonmanager.cpp"
