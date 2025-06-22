/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfos.h"

GenericNetworkModelAvailableInfos::GenericNetworkModelAvailableInfos() = default;

GenericNetworkModelAvailableInfos::~GenericNetworkModelAvailableInfos() = default;

QList<GenericNetworkModelAvailableInfo> GenericNetworkModelAvailableInfos::infos() const
{
    return mInfos;
}

void GenericNetworkModelAvailableInfos::setInfos(const QList<GenericNetworkModelAvailableInfo> &newInfos)
{
    mInfos = newInfos;
}
