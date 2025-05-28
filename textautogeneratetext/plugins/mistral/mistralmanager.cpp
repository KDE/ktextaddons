/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralmanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "mistralreply.h"
#include "mistralsettings.h"
#include "mistralutils.h"
#include <KLocalizedString>
#include <QJsonObject>
#include <QNetworkRequest>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
using namespace Qt::Literals::StringLiterals;
MistralManager::MistralManager(QObject *parent)
    : QObject{parent}
{
}

MistralManager::~MistralManager() = default;

void MistralManager::loadModels()
{
    if (mMistralAICheckConnect) {
        disconnect(mMistralAICheckConnect);
    }
    QNetworkRequest req{QUrl::fromUserInput(MistralUtils::mistralAiUrl() + MistralUtils::modelsPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mMistralAICheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", MistralUtils::mistralAiUrl(), rep->errorString());
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
}

MistralReply *MistralManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QNetworkRequest req{QUrl::fromUserInput(MistralUtils::mistralAiUrl() + MistralUtils::chatPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    req.setRawHeader("Authorization", mApiKey);
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
}

QByteArray MistralManager::apiKey() const
{
    return mApiKey;
}

void MistralManager::setApiKey(const QByteArray &newApiKey)
{
    mApiKey = newApiKey;
}

#include "moc_mistralmanager.cpp"
