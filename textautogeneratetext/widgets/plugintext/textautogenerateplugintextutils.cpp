/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateplugintextutils.h"
#include "textautogeneratetextwidget_debug.h"

#include <KConfigGroup>
#include <KSharedConfig>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGeneratePluginTextUtils::PluginUtilData TextAutoGeneratePluginTextUtils::createPluginMetaData(const KPluginMetaData &metaData)
{
    const TextAutoGeneratePluginTextUtils::PluginUtilData pluginData{
        .mIdentifier = metaData.pluginId(),
        .mName = metaData.name(),
        .mDescription = metaData.description(),
        .mEnableByDefault = metaData.isEnabledByDefault(),
    };
    if (pluginData.mName.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Plugin name not define. It's a bug:" << metaData;
    }
    return pluginData;
}

bool TextAutoGeneratePluginTextUtils::isPluginActivated(const QStringList &enabledPluginsList,
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

QPair<QStringList, QStringList> TextAutoGeneratePluginTextUtils::loadPluginSetting(const QString &groupName, const QString &prefixSettingKey)
{
    QPair<QStringList, QStringList> pair;
    KSharedConfigPtr config = KSharedConfig::openConfig();
    QStringList enabledPlugins;
    QStringList disabledPlugins;
    if (config->hasGroup(groupName)) {
        const KConfigGroup grp = config->group(groupName);
        enabledPlugins = grp.readEntry(u"%1Enabled"_s.arg(prefixSettingKey), QStringList());
        disabledPlugins = grp.readEntry(u"%1Disabled"_s.arg(prefixSettingKey), QStringList());
    }

    pair.first = enabledPlugins;
    pair.second = disabledPlugins;
    return pair;
}

void TextAutoGeneratePluginTextUtils::savePluginSettings(const QString &groupName,
                                                         const QString &prefixSettingKey,
                                                         const QStringList &enabledPluginsList,
                                                         const QStringList &disabledPluginsList)
{
    KSharedConfigPtr config = KSharedConfig::openConfig();
    KConfigGroup grp = config->group(groupName);
    grp.writeEntry(u"%1Enabled"_s.arg(prefixSettingKey), enabledPluginsList);
    grp.writeEntry(u"%1Disabled"_s.arg(prefixSettingKey), disabledPluginsList);
}
