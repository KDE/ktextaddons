/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
*/
#include "ollamamanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "ollamareply.h"
#include "ollamasettings.h"
#include "ollamautils.h"

#include <KLocalizedString>

#include <QBuffer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace Qt::Literals::StringLiterals;
OllamaManager::OllamaManager(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
{
}

OllamaManager::~OllamaManager() = default;

void OllamaManager::deleteModel(const QString &modelName)
{
    QNetworkRequest req{QUrl::fromUserInput(OllamaSettings::serverUrl().toString() + OllamaUtils::deletePath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    QJsonObject data;
    data["model"_L1] = modelName;
    auto reply = new OllamaReply{TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->sendCustomRequest(
                                     req,
                                     "DELETE",
                                     QJsonDocument(data).toJson(QJsonDocument::Compact)),
                                 OllamaReply::RequestTypes::DeleteModel,
                                 this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        // if (reply->error() == QNetworkReply::NoError) {
        Q_EMIT refreshInstalledModels();
        //}
    });
}

void OllamaManager::showModelInfo(const QString &modelName)
{
    // TODO
}

QList<OllamaModelInstalledInfo> OllamaManager::installedInfos() const
{
    return mInstalledInfos;
}

void OllamaManager::setInstalledInfos(const QList<OllamaModelInstalledInfo> &newInstalledInfos)
{
    mInstalledInfos = newInstalledInfos;
}

OllamaReply *OllamaManager::downloadModel(const QString &modelName)
{
    QNetworkRequest req{QUrl::fromUserInput(OllamaSettings::serverUrl().toString() + OllamaUtils::pullPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    QJsonObject data;
    data["model"_L1] = modelName;

    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::DownloadModel,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
        Q_EMIT downloadDone();
        Q_EMIT refreshInstalledModels();
    });
    connect(reply, &OllamaReply::downloadInProgress, this, [this, modelName](const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info) {
        Q_EMIT downloadInProgress(modelName, info);
    });
    return reply;
}

void OllamaManager::getVersion()
{
    QNetworkRequest req{QUrl::fromUserInput(OllamaSettings::serverUrl().toString() + OllamaUtils::versionPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            /*
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", OllamaSettings::serverUrl().toString(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(std::move(info));
            */
            return;
        }

        const auto json = QJsonDocument::fromJson(rep->readAll());
        qDebug() << "json " << json;
        // TODO implement it.
        /*
        ModelsInfo info;
        const auto models = json["models"_L1].toArray();
        for (const QJsonValue &model : models) {
            info.models.push_back(model["name"_L1].toString());
        }
        info.isReady = !info.models.isEmpty();
        info.hasError = false;
        Q_EMIT modelsLoadDone(std::move(info));
        */
    });
}

void OllamaManager::loadModels()
{
    if (mCheckConnect) {
        disconnect(mCheckConnect);
    }
    mInstalledInfos.clear();
    QNetworkRequest req{QUrl::fromUserInput(OllamaSettings::serverUrl().toString() + OllamaUtils::tagsPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
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
            OllamaModelInstalledInfo installed;
            installed.parseInfo(model.toObject());
            mInstalledInfos.append(std::move(installed));
            const QString name = model["name"_L1].toString();
            info.models.push_back(name);
        }
        info.isReady = !info.models.isEmpty();
        info.hasError = false;
        Q_EMIT modelsLoadDone(std::move(info));
    });
}

OllamaReply *OllamaManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QNetworkRequest req{QUrl::fromUserInput(OllamaSettings::serverUrl().toString() + OllamaUtils::completionPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    QJsonObject data;
    // data["model"_L1] = request.model().isEmpty() ? m_models.constFirst() : request.model();
    data["prompt"_L1] = request.message();
    data["model"_L1] = OllamaSettings::model();
    const auto context = request.context().toJson();
    if (!context.isNull()) {
        data["context"_L1] = context;
    }
    if (!OllamaSettings::systemPrompt().isEmpty()) {
        data["system"_L1] = OllamaSettings::systemPrompt();
    }
    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::StreamingGenerate,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
}

OllamaReply *OllamaManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
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
    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
}

bool OllamaManager::isAlreadyInstalled(const QString &modelName) const
{
    if (modelName.isEmpty()) {
        return {};
    }
    auto matchesModelName = [&](const OllamaModelInstalledInfo &info) {
        return info.model() == modelName;
    };
    auto it = std::find_if(mInstalledInfos.begin(), mInstalledInfos.end(), matchesModelName);
    if (it == mInstalledInfos.end()) {
        return false;
    }
    return true;
}

#include "moc_ollamamanager.cpp"
