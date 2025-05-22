/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfosmanager.h"
#include "autogeneratetext_ollama_debug.h"
#include "ollamamodelsinfos.h"
#include <QFile>
#include <QJsonDocument>

OllamaModelInfosManager::OllamaModelInfosManager(QObject *parent)
    : QObject{parent}
{
}

OllamaModelInfosManager::~OllamaModelInfosManager() = default;

bool OllamaModelInfosManager::loadAvailableModels()
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

    OllamaModelsInfos info;
    info.parseModelsInfo(doc.object());
    mModelInfos = info.infos();
    return true;
}

QList<OllamaModelInfo> OllamaModelInfosManager::modelInfos() const
{
    return mModelInfos;
}

void OllamaModelInfosManager::setModelInfos(const QList<OllamaModelInfo> &newModelInfos)
{
    mModelInfos = newModelInfos;
}

#include "moc_ollamamodelinfosmanager.cpp"
