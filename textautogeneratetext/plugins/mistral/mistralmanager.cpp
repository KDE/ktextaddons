/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralmanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "mistralreply.h"
#include "mistralutils.h"

MistralManager::MistralManager(QObject *parent)
    : QObject{parent}
{
}

MistralManager::~MistralManager() = default;

void MistralManager::loadModels()
{
    // TODO
}

#if 0

MistralReply *MistralManager::getChatCompletion(const OllamaRequest &request)
{
    QNetworkRequest req{QUrl::fromUserInput(OllamaSettings::serverUrl().toString() + OllamaUtils::chatPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    QJsonObject data;
    data["model"_L1] = OllamaSettings::model();
    data["messages"_L1] = request.messages();
    /*
    if (!OllamaSettings::systemPrompt().isEmpty()) {
        data["system"_L1] = OllamaSettings::systemPrompt();
    }
    */
    auto reply = new MistralReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
}
#endif
#include "moc_mistralmanager.cpp"
