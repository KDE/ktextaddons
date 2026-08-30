/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pluginutil.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;

bool TextAddonsWidgets::PluginUtil::isPluginActivated(const QStringList &enabledPluginsList,
                                                      const QStringList &disabledPluginsList,
                                                      bool isEnabledByDefault,
                                                      const QString &pluginId)
{
    if (pluginId.isEmpty()) {
        return false;
    }
    const bool pluginEnabledByUser = enabledPluginsList.contains(pluginId);
    const bool pluginDisabledByUser = disabledPluginsList.contains(pluginId);
    if ((isEnabledByDefault && !pluginDisabledByUser) || (!isEnabledByDefault && pluginEnabledByUser)) {
        return true;
    }
    return false;
}

TextAddonsWidgets::PluginUtil::PluginsStateList
TextAddonsWidgets::PluginUtil::loadPluginSetting(const QString &configFileName, const QString &groupName, const QString &prefixSettingKey)
{
    PluginUtil::PluginsStateList pair;
    KSharedConfigPtr config = KSharedConfig::openConfig(configFileName);
    QStringList enabledPlugins;
    QStringList disabledPlugins;
    if (config->hasGroup(groupName)) {
        const KConfigGroup grp = config->group(groupName);
        enabledPlugins = grp.readEntry(u"%1Enabled"_s.arg(prefixSettingKey), QStringList());
        disabledPlugins = grp.readEntry(u"%1Disabled"_s.arg(prefixSettingKey), QStringList());
    }

    pair.enabledPluginList = enabledPlugins;
    pair.disabledPluginList = disabledPlugins;
    return pair;
}

void TextAddonsWidgets::PluginUtil::savePluginSettings(const QString &groupName,
                                                       const QString &prefixSettingKey,
                                                       const QStringList &enabledPluginsList,
                                                       const QStringList &disabledPluginsList,
                                                       const QString &configFileName)
{
    KSharedConfigPtr config = KSharedConfig::openConfig(configFileName);
    // qDebug() << " void TextAddonsWidgets::PluginUtil::savePluginSettings(const QString &groupName,  " << configFileName;
    KConfigGroup grp = config->group(groupName);
    if (enabledPluginsList.isEmpty()) {
        grp.deleteEntry(u"%1Enabled"_s.arg(prefixSettingKey));
    } else {
        grp.writeEntry(u"%1Enabled"_s.arg(prefixSettingKey), enabledPluginsList);
    }
    if (disabledPluginsList.isEmpty()) {
        grp.deleteEntry(u"%1Disabled"_s.arg(prefixSettingKey));
    } else {
        grp.writeEntry(u"%1Disabled"_s.arg(prefixSettingKey), disabledPluginsList);
    }
}

TextAddonsWidgets::PluginUtilData TextAddonsWidgets::PluginUtil::createPluginMetaData(const KPluginMetaData &metaData)
{
    PluginUtilData pluginData;
    pluginData.mDescription = metaData.description();
    pluginData.mName = metaData.name();
    pluginData.mIdentifier = metaData.pluginId();
    pluginData.mEnableByDefault = metaData.isEnabledByDefault();
    return pluginData;
}
