/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategenericnetwork_export.h"
#include <QJsonObject>
#include <QString>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkModelAvailableInfo
{
public:
    GenericNetworkModelAvailableInfo();
    ~GenericNetworkModelAvailableInfo();
    void parseInfo(const QString &name, const QJsonObject &obj);
};
