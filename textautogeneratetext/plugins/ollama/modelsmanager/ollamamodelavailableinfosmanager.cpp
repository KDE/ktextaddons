/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfosmanager.h"
#include "autogeneratetext_ollama_debug.h"
#include "ollamamodelsavalableinfos.h"
#include <QFile>
#include <QJsonDocument>

OllamaModelAvailableInfosManager::OllamaModelAvailableInfosManager(QObject *parent)
    : QObject{parent}
{
}

OllamaModelAvailableInfosManager::~OllamaModelAvailableInfosManager() = default;

bool OllamaModelAvailableInfosManager::loadAvailableModels()
{
    QFile f(QStringLiteral(":/available_models"));
    if (!f.open(QIODevice::ReadOnly)) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to load:" << f.fileName();
        return false;
    }
    const auto content = f.readAll();
    f.close();
    QJsonParseError error;
    const auto doc = QJsonDocument::fromJson(content, &error);

    OllamaModelsAvalableInfos info;
    info.parseModelsInfo(doc.object());
    mModelInfos = info.infos();
    return true;
}

QList<OllamaModelAvailableInfo> OllamaModelAvailableInfosManager::modelInfos() const
{
    return mModelInfos;
}

void OllamaModelAvailableInfosManager::setModelInfos(const QList<OllamaModelAvailableInfo> &newModelInfos)
{
    mModelInfos = newModelInfos;
}

#include "moc_ollamamodelavailableinfosmanager.cpp"
