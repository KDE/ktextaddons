/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelavailableinfosmanager.h"

#include "autogeneratetext_ollamacommon_debug.h"
#include "ollamacommonmodelsavalableinfos.h"
#include <QFile>
#include <QJsonDocument>

using namespace Qt::Literals::StringLiterals;
OllamaCommonModelAvailableInfosManager::OllamaCommonModelAvailableInfosManager(QObject *parent)
    : QObject{parent}
{
}

OllamaCommonModelAvailableInfosManager::~OllamaCommonModelAvailableInfosManager() = default;

bool OllamaCommonModelAvailableInfosManager::loadAvailableModels()
{
    QFile f(u":/available_models"_s);
    if (!f.open(QIODevice::ReadOnly)) {
        qCWarning(AUTOGENERATETEXT_OLLAMACOMMON_LOG) << "Impossible to load:" << f.fileName();
        return false;
    }
    const auto content = f.readAll();
    f.close();
    QJsonParseError error;
    const auto doc = QJsonDocument::fromJson(content, &error);

    OllamaCommonModelsAvalableInfos info;
    info.parseModelsInfo(doc.object());
    mModelInfos = info.infos();
    return true;
}

QList<OllamaCommonModelAvailableInfo> OllamaCommonModelAvailableInfosManager::modelInfos() const
{
    return mModelInfos;
}

void OllamaCommonModelAvailableInfosManager::setModelInfos(const QList<OllamaCommonModelAvailableInfo> &newModelInfos)
{
    mModelInfos = newModelInfos;
}

OllamaCommonModelAvailableInfo OllamaCommonModelAvailableInfosManager::modelInfo(const QString &modelName) const
{
    if (modelName.isEmpty()) {
        return {};
    }
    auto matchesModelName = [&](const OllamaCommonModelAvailableInfo &info) {
        return info.name() == modelName;
    };
    auto it = std::find_if(mModelInfos.begin(), mModelInfos.end(), matchesModelName);
    if (it != mModelInfos.end()) {
        return *it;
    }
    return {};
}

#include "moc_ollamacommonmodelavailableinfosmanager.cpp"
