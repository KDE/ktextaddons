/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelsavalableinfos.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
OllamaCommonModelsAvalableInfos::OllamaCommonModelsAvalableInfos() = default;

void OllamaCommonModelsAvalableInfos::parseModelsInfo(const QJsonObject &obj)
{
    QList<OllamaCommonModelAvailableInfo> lstInfo;
    lstInfo.reserve(obj.size());
    for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
        OllamaCommonModelAvailableInfo info;
        info.parseInfo(it.key(), it.value().toObject());
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
