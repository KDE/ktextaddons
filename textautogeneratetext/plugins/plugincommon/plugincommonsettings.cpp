/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "plugincommonsettings.h"
#include "autogeneratetext_plugincommon_debug.h"
#include <KConfigGroup>
using namespace Qt::Literals::StringLiterals;

PluginCommonSettings::PluginCommonSettings() = default;
PluginCommonSettings::~PluginCommonSettings() = default;

double PluginCommonSettings::defaultTemperature() const
{
    return 0.8;
}
void PluginCommonSettings::load(const KConfigGroup &config)
{
    setDisplayName(config.readEntry(u"Name"_s));
    setCurrentModel(config.readEntry(u"CurrentModel"_s));
    if (config.hasKey(u"Temperature"_s)) {
        setTemperature(config.readEntry(u"Temperature"_s, defaultTemperature()));
    }
}

void PluginCommonSettings::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, displayName());
    config.writeEntry(u"CurrentModel"_s, currentModel());
    config.writeEntry(u"Temperature"_s, temperature());
}

QString PluginCommonSettings::displayName() const
{
    return mDisplayName;
}

void PluginCommonSettings::setDisplayName(const QString &newName)
{
    mDisplayName = newName;
}

QString PluginCommonSettings::currentModel() const
{
    return mCurrentModel;
}

void PluginCommonSettings::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}

PluginCommonSettings::ShareNameType PluginCommonSettings::shareNameType() const
{
    return mShareNameType;
}

PluginCommonSettings::ShareNameType PluginCommonSettings::defaultShareNameType()
{
    return PluginCommonSettings::ShareNameType::DoNotShare;
}

void PluginCommonSettings::setShareNameType(const PluginCommonSettings::ShareNameType &newShareNameType)
{
    mShareNameType = newShareNameType;
}

PluginCommonSettings::ShareNameType PluginCommonSettings::convertShareNameTypeFromString(const QString &str)
{
    if (str == "DoNotShare"_L1) {
        return PluginCommonSettings::ShareNameType::DoNotShare;
    } else if (str == "UserName"_L1) {
        return PluginCommonSettings::ShareNameType::UserName;
    } else if (str == "FullName"_L1) {
        return PluginCommonSettings::ShareNameType::FullName;
    }
    qCWarning(AUTOGENERATETEXT_PLUGINCOMMON_LOG) << "Invalid ShareNameType: " << str;
    return PluginCommonSettings::ShareNameType::DoNotShare;
}

QString PluginCommonSettings::convertShareNameTypeToString(PluginCommonSettings::ShareNameType type)
{
    switch (type) {
    case ShareNameType::DoNotShare:
        return u"DoNotShare"_s;
    case ShareNameType::UserName:
        return u"UserName"_s;
    case ShareNameType::FullName:
        return u"FullName"_s;
    }

    return {};
}

bool PluginCommonSettings::thoughtProcessing() const
{
    return mThoughtProcessing;
}

void PluginCommonSettings::setThoughtProcessing(bool newThoughtProcessing)
{
    mThoughtProcessing = newThoughtProcessing;
}

double PluginCommonSettings::temperature() const
{
    return mTemperature;
}

void PluginCommonSettings::setTemperature(double newTemperature)
{
    mTemperature = newTemperature;
}

#include "moc_plugincommonsettings.cpp"
