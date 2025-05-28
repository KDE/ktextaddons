/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaimanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "openaireply.h"
// #include "mistralutils.h"
#include <KLocalizedString>
#include <QJsonObject>
#include <QNetworkRequest>
#include <qnetworkaccessmanager.h>
using namespace Qt::Literals::StringLiterals;
OpenAIManager::OpenAIManager(QObject *parent)
    : QObject{parent}
{
}

OpenAIManager::~OpenAIManager() = default;

void OpenAIManager::loadModels()
{
#if 0
    if (mOllamaCheckConnect) {
        disconnect(mOllamaCheckConnect);
    }
    QNetworkRequest req{QUrl::fromUserInput(MistralSettings::serverUrl().toString() + MistralUtils::tagsPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mOllamaCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", MistralUtils::serverUrl().toString(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(std::move(info));
            return;
        }

        ModelsInfo info;
        const auto json = QJsonDocument::fromJson(rep->readAll());
        const auto models = json["models"_L1].toArray();
        for (const QJsonValue &model : models) {
            info.models.push_back(model["name"_L1].toString());
        }
        info.isReady = !info.models.isEmpty();
        info.hasError = false;
        Q_EMIT modelsLoadDone(std::move(info));
    });
#endif
}

OpenAIReply *OpenAIManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
#if 0
    QNetworkRequest req{QUrl::fromUserInput(MistralSettings::serverUrl().toString() + MistralUtils::chatPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    req.setRawHeader("Authorization", QByteArray("Bearer YOUR_API_KEY"));
    QJsonObject data;
    data["model"_L1] = MistralSettings::model();
    data["messages"_L1] = request.messages();
    /*
    if (!OllamaSettings::systemPrompt().isEmpty()) {
        data["system"_L1] = OllamaSettings::systemPrompt();
    }
    */
    auto reply = new MistralReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        MistralReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &MistralReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
#endif
    return nullptr;
}

QString OpenAIManager::apiKey() const
{
    return mApiKey;
}

void OpenAIManager::setApiKey(const QString &newApiKey)
{
    mApiKey = newApiKey;
}

#include "moc_openaimanager.cpp"
