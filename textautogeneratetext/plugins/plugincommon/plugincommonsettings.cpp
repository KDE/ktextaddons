/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "plugincommonsettings.h"
using namespace Qt::Literals::StringLiterals;

PluginCommonSettings::PluginCommonSettings() = default;
PluginCommonSettings::~PluginCommonSettings() = default;

PluginCommonSettings::ShareNameType PluginCommonSettings::shareNameType() const
{
    return mShareNameType;
}

PluginCommonSettings::ShareNameType PluginCommonSettings::defaultShareNameType() const
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
