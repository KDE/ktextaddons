/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerategenericnetwork_export.h"
#include <KPageDialog>
class GenericNetworkAvailableModelWidget;
class GenericNetworkManager;
class GenericNetworkNetworkPluginConfigureWidget;
class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkConfigureDialog : public KPageDialog
{
    Q_OBJECT
public:
    explicit GenericNetworkConfigureDialog(GenericNetworkManager *manager, QWidget *parent = nullptr);
    ~GenericNetworkConfigureDialog() override;

private:
    TEXTAUTOGENERATEGENERICNETWORK_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATEGENERICNETWORK_NO_EXPORT void readConfig();
    TEXTAUTOGENERATEGENERICNETWORK_NO_EXPORT void slotAccepted();
    GenericNetworkNetworkPluginConfigureWidget *const mConfigureWidget;
    GenericNetworkAvailableModelWidget *const mAvailableModelWidget;
};
