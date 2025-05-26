/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsinfos.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
OllamaModelsInfos::OllamaModelsInfos() = default;

OllamaModelsInfos::~OllamaModelsInfos() = default;

void OllamaModelsInfos::parseModelsInfo(const QJsonObject &obj)
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

QList<OllamaModelAvailableInfo> OllamaModelsInfos::infos() const
{
    return mInfos;
}

void OllamaModelsInfos::setInfos(const QList<OllamaModelAvailableInfo> &newInfos)
{
    mInfos = newInfos;
}
