/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"

#include <KPluginMetaData>
#include <QString>
#include <QStringList>

namespace TextAddonsWidgets
{
/**
 * @brief The PluginUtilData class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT PluginUtilData
{
public:
    PluginUtilData() = default;

    QStringList mExtraInfo;
    QString mDescription;
    QString mIdentifier;
    QString mName;
    bool mEnableByDefault = false;
    bool mHasConfigureDialog = false;
};

namespace PluginUtil
{
struct TEXTADDONSWIDGETS_EXPORT PluginsStateList {
    QStringList enabledPluginList;
    QStringList disabledPluginList;
};

[[nodiscard]] TEXTADDONSWIDGETS_EXPORT bool
isPluginActivated(const QStringList &enabledPluginsList, const QStringList &disabledPluginsList, bool isEnabledByDefault, const QString &pluginId);

[[nodiscard]] TEXTADDONSWIDGETS_EXPORT PluginsStateList loadPluginSetting(const QString &configFileName,
                                                                          const QString &groupName,
                                                                          const QString &prefixSettingKey);
TEXTADDONSWIDGETS_EXPORT void savePluginSettings(const QString &groupName,
                                                 const QString &prefixSettingKey,
                                                 const QStringList &enabledPluginsList,
                                                 const QStringList &disabledPluginsList,
                                                 const QString &configFileName = {});
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT TextAddonsWidgets::PluginUtilData createPluginMetaData(const KPluginMetaData &metaData);
}
}
