/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworksettings.h"
#include <KConfigGroup>
using namespace Qt::Literals::StringLiterals;
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

void GenericNetworkSettings::load(const KConfigGroup &config)
{
    PluginCommonSettings::load(config);
    setTemperature(config.readEntry(u"Temperature"_s, 0.8));
    setMaxTokens(config.readEntry(u"MaxToken"_s, 2048));
    setSeed(config.readEntry(u"Seed"_s, 0));
}

void GenericNetworkSettings::save(KConfigGroup &config)
{
    PluginCommonSettings::save(config);
    config.writeEntry(u"MaxToken"_s, maxTokens());
    config.writeEntry(u"Temperature"_s, temperature());
    config.writeEntry(u"Seed"_s, seed());
}
