/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfos.h"
#include <QJsonObject>

GenericNetworkModelAvailableInfos::GenericNetworkModelAvailableInfos() = default;

GenericNetworkModelAvailableInfos::~GenericNetworkModelAvailableInfos() = default;

void GenericNetworkModelAvailableInfos::parseModelsInfo(const QJsonArray &array)
{
    QList<GenericNetworkModelAvailableInfo> lstInfo;
    for (int i = 0; i < array.count(); ++i) {
        GenericNetworkModelAvailableInfo info;
        info.parseInfo(array[i].toObject());
        lstInfo.append(std::move(info));
    }
    mInfos = std::move(lstInfo);
}

QList<GenericNetworkModelAvailableInfo> GenericNetworkModelAvailableInfos::infos() const
{
    return mInfos;
}

void GenericNetworkModelAvailableInfos::setInfos(const QList<GenericNetworkModelAvailableInfo> &newInfos)
{
    mInfos = newInfos;
}
