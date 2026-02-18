/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"

#include <KPluginMetaData>
#include <QString>
#include <QStringList>

namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::PluginUtil
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/PluginUtil
 *
 * \brief The PluginUtilData class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT PluginUtilData
{
public:
    /*!
     * \brief Constructor for PluginUtilData
     */
    PluginUtilData() = default;

    /*!
     * \brief Extra information about the plugin
     */
    QStringList mExtraInfo;
    /*!
     * \brief Description of the plugin
     */
    QString mDescription;
    /*!
     * \brief Unique identifier for the plugin
     */
    QString mIdentifier;
    /*!
     * \brief Name of the plugin
     */
    QString mName;
    /*!
     * \brief Whether the plugin is enabled by default
     */
    bool mEnableByDefault = false;
    /*!
     * \brief Whether the plugin has a configure dialog
     */
    bool mHasConfigureDialog = false;
};

namespace PluginUtil
{
/*!
 * \class TextAddonsWidgets::PluginUtil::PluginsStateList
 * \brief Structure holding lists of enabled and disabled plugins
 */
struct TEXTADDONSWIDGETS_EXPORT PluginsStateList {
    /*!
     * \brief List of enabled plugin identifiers
     */
    QStringList enabledPluginList;
    /*!
     * \brief List of disabled plugin identifiers
     */
    QStringList disabledPluginList;
};

/*!
 * \brief Checks if a plugin is activated
 * \param enabledPluginsList List of enabled plugin identifiers
 * \param disabledPluginsList List of disabled plugin identifiers
 * \param isEnabledByDefault Whether the plugin is enabled by default
 * \param pluginId The plugin identifier to check
 * \return True if the plugin is activated, false otherwise
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT bool
isPluginActivated(const QStringList &enabledPluginsList, const QStringList &disabledPluginsList, bool isEnabledByDefault, const QString &pluginId);

/*!
 * \brief Loads plugin state from configuration file
 * \param configFileName The configuration file name
 * \param groupName The configuration group name
 * \param prefixSettingKey The prefix for the setting keys
 * \return PluginsStateList containing enabled and disabled plugin lists
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT PluginsStateList loadPluginSetting(const QString &configFileName,
                                                                          const QString &groupName,
                                                                          const QString &prefixSettingKey);
/*!
 * \brief Saves plugin settings to configuration file
 * \param groupName The configuration group name
 * \param prefixSettingKey The prefix for the setting keys
 * \param enabledPluginsList List of enabled plugin identifiers
 * \param disabledPluginsList List of disabled plugin identifiers
 * \param configFileName The configuration file name (optional)
 */
TEXTADDONSWIDGETS_EXPORT void savePluginSettings(const QString &groupName,
                                                 const QString &prefixSettingKey,
                                                 const QStringList &enabledPluginsList,
                                                 const QStringList &disabledPluginsList,
                                                 const QString &configFileName = {});
/*!
 * \brief Creates PluginUtilData from KPluginMetaData
 * \param metaData The plugin metadata
 * \return PluginUtilData containing plugin information
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT TextAddonsWidgets::PluginUtilData createPluginMetaData(const KPluginMetaData &metaData);
}
}
