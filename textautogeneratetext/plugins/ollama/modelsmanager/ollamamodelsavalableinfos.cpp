/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsavalableinfos.h"

using namespace Qt::Literals::StringLiterals;
OllamaModelsAvalableInfos::OllamaModelsAvalableInfos() = default;

OllamaModelsAvalableInfos::~OllamaModelsAvalableInfos() = default;

void OllamaModelsAvalableInfos::parseModelsInfo(const QJsonObject &obj)
{
    QList<OllamaModelAvailableInfo> lstInfo;
    const QStringList keys = obj.keys();
    for (const auto &k : keys) {
        OllamaModelAvailableInfo info;
        info.parseInfo(k, obj[k].toObject());
        lstInfo.append(std::move(info));
    }
    mInfos = std::move(lstInfo);
}

QList<OllamaModelAvailableInfo> OllamaModelsAvalableInfos::infos() const
{
    return mInfos;
}

void OllamaModelsAvalableInfos::setInfos(const QList<OllamaModelAvailableInfo> &newInfos)
{
    mInfos = newInfos;
}
