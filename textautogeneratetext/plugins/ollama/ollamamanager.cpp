/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "ollamasettings.h"
#include "ollamautils.h"

#include <KLocalizedString>

#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace Qt::Literals::StringLiterals;
OllamaManager::OllamaManager(QObject *parent)
    : QObject{parent}
{
}

OllamaManager::~OllamaManager() = default;

OllamaManager *OllamaManager::self()
{
    static OllamaManager s_self;
    return &s_self;
}

void OllamaManager::loadModels()
{
    QNetworkRequest req{QUrl::fromUserInput(OllamaSettings::serverUrl().toString() + OllamaUtils::tagsPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    auto rep = TextAutogenerateText::TextAutogenerateEngineAccessManager::self()->networkManager()->get(req);
    mOllamaCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", OllamaSettings::serverUrl().toString(), rep->errorString());
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

QDebug operator<<(QDebug d, const OllamaManager::ModelsInfo &t)
{
    d.space() << "models:" << t.models;
    d.space() << "hasError:" << t.hasError;
    d.space() << "isReady:" << t.isReady;
    return d;
}
#include "moc_ollamamanager.cpp"
