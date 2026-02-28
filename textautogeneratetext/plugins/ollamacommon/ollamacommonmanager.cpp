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

bool OllamaCommonManager::hasVisionSupport(const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Vision);
}

bool OllamaCommonManager::hasToolsSupport(const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Tools);
}

bool OllamaCommonManager::hasOcrSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasAudioSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasThinkSupport(const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Reasoning);
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

void OllamaCommonManager::getVersion()
{
    QUrl url = instanceUrl();
    url.setPath(OllamaCommonUtils::versionPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [rep] {
        if (rep->error() != QNetworkReply::NoError) {
            qWarning() << "Error during getting version";
            return;
        }

        const auto json = QJsonDocument::fromJson(rep->readAll());
        qDebug() << "json " << json;
    });
}

bool OllamaCommonManager::hasCategorySupport([[maybe_unused]] const QString &modelName,
                                             [[maybe_unused]] TextAutoGenerateText::TextAutoGenerateManager::Category cat) const
{
    return false;
}

void OllamaCommonManager::addKeepAliveType(QJsonObject &data, OllamaCommonSettings::KeepAliveType type, int keepAliveMinutes)
{
    switch (type) {
    case OllamaCommonSettings::KeepAliveType::KeepAliveForever:
        data["keep_alive"_L1] = -1;
        break;
    case OllamaCommonSettings::KeepAliveType::SetTimer:
        data["keep_alive"_L1] = keepAliveMinutes * 60;
        break;
    case OllamaCommonSettings::KeepAliveType::UnloadAfterUse:
        data["keep_alive"_L1] = 1;
        break;
    case OllamaCommonSettings::KeepAliveType::Unknown:
        break;
    }
}
#include "moc_ollamacommonmanager.cpp"
