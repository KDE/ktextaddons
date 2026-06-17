/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworksettings.h"

GenericNetworkSettings::GenericNetworkSettings() = default;

GenericNetworkSettings::~GenericNetworkSettings() = default;

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

int GenericNetworkSettings::seed() const
{
    return mSeed;
}

void GenericNetworkSettings::setSeed(int newSeed)
{
    mSeed = newSeed;
}
