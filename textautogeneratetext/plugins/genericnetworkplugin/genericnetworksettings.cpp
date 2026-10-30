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
    setMaxTokens(config.readEntry(u"MaxToken"_s, 2048));
    setSeed(config.readEntry(u"Seed"_s, 0));
    setCustomUrl(config.readEntry(u"CustomUrl"_s, QString()));
    setCustomModels(config.readEntry(u"CustomModels"_s, QStringList()));
}

void GenericNetworkSettings::save(KConfigGroup &config)
{
    PluginCommonSettings::save(config);
    config.writeEntry(u"MaxToken"_s, maxTokens());
    config.writeEntry(u"Seed"_s, seed());
    if (const auto value = customUrl(); !value.isEmpty()) {
        config.writeEntry(u"CustomUrl"_s, value);
    } else {
        config.deleteEntry(u"CustomUrl"_s);
    }
    if (const auto value = customModels(); !value.isEmpty()) {
        config.writeEntry(u"CustomModels"_s, value);
    } else {
        config.deleteEntry(u"CustomModels"_s);
    }
}

QString GenericNetworkSettings::customUrl() const
{
    return mCustomUrl;
}

void GenericNetworkSettings::setCustomUrl(const QString &newCustomUrl)
{
    mCustomUrl = newCustomUrl;
}

QStringList GenericNetworkSettings::customModels() const
{
    return mCustomModels;
}

void GenericNetworkSettings::setCustomModels(const QStringList &newCustomModels)
{
    mCustomModels = newCustomModels;
}
