/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralmanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "mistralreply.h"
#include "mistralsettings.h"
#include "mistralutils.h"
#include <QJsonObject>
#include <QNetworkRequest>
#include <qnetworkaccessmanager.h>
using namespace Qt::Literals::StringLiterals;
MistralManager::MistralManager(QObject *parent)
    : QObject{parent}
{
}

MistralManager::~MistralManager() = default;

void MistralManager::loadModels()
{
    // TODO
}

MistralReply *MistralManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QNetworkRequest req{QUrl::fromUserInput(MistralSettings::serverUrl().toString() + MistralUtils::chatPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
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
        // TODO Q_EMIT finished(reply->readResponse());
    });
    return reply;
}

#include "moc_mistralmanager.cpp"
