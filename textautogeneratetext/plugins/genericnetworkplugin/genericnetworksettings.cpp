/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworksettings.h"

GenericNetworkSettings::GenericNetworkSettings() = default;

GenericNetworkSettings::~GenericNetworkSettings() = default;

QString GenericNetworkSettings::displayName() const
{
    return mDisplayName;
}

void GenericNetworkSettings::setDisplayName(const QString &newDisplayName)
{
    mDisplayName = newDisplayName;
}

QString GenericNetworkSettings::currentModel() const
{
    return mCurrentModel;
}

int GenericNetworkSettings::maxTokens() const
{
    return mMaxTokens;
}

void GenericNetworkSettings::setMaxTokens(int newMaxTokens)
{
    mMaxTokens = newMaxTokens;
}

double GenericNetworkSettings::temperature() const
{
    return mTemperature;
}

void GenericNetworkSettings::setTemperature(double newTemperature)
{
    mTemperature = newTemperature;
}

void GenericNetworkSettings::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}
