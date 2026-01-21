/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelsavalableinfos.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
OllamaCommonModelsAvalableInfos::OllamaCommonModelsAvalableInfos() = default;

OllamaCommonModelsAvalableInfos::~OllamaCommonModelsAvalableInfos() = default;

void OllamaCommonModelsAvalableInfos::parseModelsInfo(const QJsonObject &obj)
{
    QList<OllamaCommonModelAvailableInfo> lstInfo;
    const QStringList keys = obj.keys();
    for (const auto &k : keys) {
        OllamaCommonModelAvailableInfo info;
        info.parseInfo(k, obj[k].toObject());
        lstInfo.append(std::move(info));
    }
    mInfos = std::move(lstInfo);
}

QList<OllamaCommonModelAvailableInfo> OllamaCommonModelsAvalableInfos::infos() const
{
    return mInfos;
}

void OllamaCommonModelsAvalableInfos::setInfos(const QList<OllamaCommonModelAvailableInfo> &newInfos)
{
    mInfos = newInfos;
}
