/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategenericnetwork_export.h"
#include <QString>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkSettings
{
public:
    GenericNetworkSettings();
    ~GenericNetworkSettings();

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newDisplayName);

    void setCurrentModel(const QString &newCurrentModel);
    [[nodiscard]] QString currentModel() const;

    [[nodiscard]] int maxTokens() const;
    void setMaxTokens(int newMaxTokens);

    [[nodiscard]] double temperature() const;
    void setTemperature(double newTemperature);

    [[nodiscard]] int seed() const;
    void setSeed(int newSeed);

private:
    QString mDisplayName;
    QString mCurrentModel;
    int mMaxTokens = 2048;
    int mSeed = 0;
    double mTemperature = 0.8;
};
