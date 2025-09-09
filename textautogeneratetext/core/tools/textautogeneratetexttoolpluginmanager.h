/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "core/textautogenerateplugintextutils.h"
#include "textautogeneratetext_private_export.h"
#include <KPluginMetaData>
#include <QList>
#include <QObject>

namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolPlugin;
class TextAutoGenerateTextToolPluginManagerInfo
{
public:
    TextAutoGenerateTextToolPluginManagerInfo() = default;

    KPluginMetaData data;
    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    TextAutoGeneratePluginTextUtils::PluginUtilData pluginData;
    TextAutoGenerateTextToolPlugin *plugin = nullptr;
    bool isEnabled = true;
};

class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextToolPluginManager final : public QObject
{
    Q_OBJECT
public:
    ~TextAutoGenerateTextToolPluginManager() override;
    static TextAutoGenerateTextToolPluginManager *self();

    [[nodiscard]] QList<TextAutoGenerateTextToolPlugin *> pluginsList() const;

    [[nodiscard]] QString configGroupName() const;
    [[nodiscard]] QString configPrefixSettingKey() const;

    [[nodiscard]] QList<TextAutoGeneratePluginTextUtils::PluginUtilData> pluginDataList() const;

    [[nodiscard]] TextAutoGenerateTextToolPlugin *pluginFromIdentifier(const QString &identifier) const;

private:
    explicit TextAutoGenerateTextToolPluginManager(QObject *parent = nullptr);
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializePluginList();
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadPlugin(TextAutoGenerateTextToolPluginManagerInfo *item);
    QList<TextAutoGenerateTextToolPluginManagerInfo> mPluginList;
    QList<TextAutoGeneratePluginTextUtils::PluginUtilData> mPluginDataList;
};
}
