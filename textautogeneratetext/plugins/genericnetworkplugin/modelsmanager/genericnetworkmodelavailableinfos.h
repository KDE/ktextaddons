/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "genericnetworkmodelavailableinfo.h"
#include "textautogenerategeneric_private_export.h"

class TEXTAUTOGENERATEGENERICNETWORK_TESTS_EXPORT GenericNetworkModelAvailableInfos
{
public:
    GenericNetworkModelAvailableInfos();
    ~GenericNetworkModelAvailableInfos();

    [[nodiscard]] QList<GenericNetworkModelAvailableInfo> infos() const;
    void setInfos(const QList<GenericNetworkModelAvailableInfo> &newInfos);

private:
    QList<GenericNetworkModelAvailableInfo> mInfos;
};
Q_DECLARE_TYPEINFO(GenericNetworkModelAvailableInfos, Q_RELOCATABLE_TYPE);
