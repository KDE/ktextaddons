/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "plugincommonsettings.h"
#include "textautogenerategenericnetwork_export.h"
#include <QString>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkSettings : public PluginCommonSettings
{
public:
    GenericNetworkSettings();
    virtual ~GenericNetworkSettings();

    [[nodiscard]] int maxTokens() const;
    void setMaxTokens(int newMaxTokens);

    [[nodiscard]] double temperature() const;
    void setTemperature(double newTemperature);

    [[nodiscard]] int seed() const;
    void setSeed(int newSeed);

private:
    int mMaxTokens = 2048;
    int mSeed = 0;
    double mTemperature = 0.8;
};
