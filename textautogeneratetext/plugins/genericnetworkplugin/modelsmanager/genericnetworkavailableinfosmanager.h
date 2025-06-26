/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategeneric_private_export.h"
#include <QObject>

class TEXTAUTOGENERATEGENERICNETWORK_TESTS_EXPORT GenericNetworkAvailableInfosManager : public QObject
{
    Q_OBJECT
public:
    explicit GenericNetworkAvailableInfosManager(QObject *parent = nullptr);
    ~GenericNetworkAvailableInfosManager() override;
};
