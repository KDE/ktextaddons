/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonscore_export.h"

#include <KPluginMetaData>

#include <QStringList>

namespace TextAddonsCore
{
/*!
 * \class TextAddonsCore::PluginUtilData
 * \inmodule TextAddonsCore
 * \inheaderfile TextAddonsCore/PluginUtil
 *
 * \brief The PluginUtilData class holds the information about a plugin.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSCORE_EXPORT PluginUtilData
{
public:
    /*!
     * \brief Constructor for PluginUtilData.
     */
    PluginUtilData() = default;

    /*!
     * \brief Extra information about the plugin.
     */
    QStringList mExtraInfo;
    /*!
     * \brief Description of the plugin.
     */
    QString mDescription;
    /*!
     * \brief Unique identifier for the plugin.
     */
    QString mIdentifier;
    /*!
     * \brief Name of the plugin.
     */
    QString mName;
    /*!
     * \brief Whether the plugin is enabled by default.
     */
    bool mEnableByDefault = false;
    /*!
     * \brief Whether the plugin has a configure dialog.
     */
    bool mHasConfigureDialog = false;
};

/*!
 * \namespace TextAddonsCore::PluginUtil
 * \inmodule TextAddonsCore
 * \inheaderfile TextAddonsCore/PluginUtil
 *
 * \brief Helper functions to load and save the plugin activation state.
 */
namespace PluginUtil
{
/*!
 * \class TextAddonsCore::PluginUtil::PluginsStateList
 * \inmodule TextAddonsCore
 * \inheaderfile TextAddonsCore/PluginUtil
 *
 * \brief Structure holding lists of enabled and disabled plugins.
 */
struct TEXTADDONSCORE_EXPORT PluginsStateList {
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
 * \brief Returns true if the plugin \a pluginId is activated.
 *
 * If \a isEnabledByDefault is true, the plugin is activated unless it is in
 * \a disabledPluginsList, otherwise it is activated only if it is in
 * \a enabledPluginsList. Returns false if \a pluginId is empty.
 */
[[nodiscard]] TEXTADDONSCORE_EXPORT bool
isPluginActivated(const QStringList &enabledPluginsList, const QStringList &disabledPluginsList, bool isEnabledByDefault, const QString &pluginId);

/*!
 * \brief Loads the plugin state from the configuration file \a configFileName.
 *
 * Reads the \a prefixSettingKey Enabled and Disabled entries of the \a groupName
 * group and returns them as a PluginsStateList.
 */
[[nodiscard]] TEXTADDONSCORE_EXPORT PluginsStateList loadPluginSetting(const QString &configFileName,
                                                                       const QString &groupName,
                                                                       const QString &prefixSettingKey);
/*!
 * \brief Saves the plugin settings to the configuration file \a configFileName.
 *
 * Writes \a enabledPluginsList and \a disabledPluginsList to the
 * \a prefixSettingKey Enabled and Disabled entries of the \a groupName group.
 * Empty lists remove the corresponding entry. If \a configFileName is empty,
 * the application configuration file is used.
 */
TEXTADDONSCORE_EXPORT void savePluginSettings(const QString &groupName,
                                              const QString &prefixSettingKey,
                                              const QStringList &enabledPluginsList,
                                              const QStringList &disabledPluginsList,
                                              const QString &configFileName = {});
/*!
 * \brief Returns a PluginUtilData filled from the plugin \a metaData.
 */
[[nodiscard]] TEXTADDONSCORE_EXPORT TextAddonsCore::PluginUtilData createPluginMetaData(const KPluginMetaData &metaData);
}
}
