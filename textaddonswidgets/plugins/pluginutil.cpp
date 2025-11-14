/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pluginutil.h"
#include <KConfigGroup>
#include <KSharedConfig>

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
        enabledPlugins = grp.readEntry(QStringLiteral("%1Enabled").arg(prefixSettingKey), QStringList());
        disabledPlugins = grp.readEntry(QStringLiteral("%1Disabled").arg(prefixSettingKey), QStringList());
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
        grp.deleteEntry(QStringLiteral("%1Enabled").arg(prefixSettingKey));
    } else {
        grp.writeEntry(QStringLiteral("%1Enabled").arg(prefixSettingKey), enabledPluginsList);
    }
    if (disabledPluginsList.isEmpty()) {
        grp.deleteEntry(QStringLiteral("%1Disabled").arg(prefixSettingKey));
    } else {
        grp.writeEntry(QStringLiteral("%1Disabled").arg(prefixSettingKey), disabledPluginsList);
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
