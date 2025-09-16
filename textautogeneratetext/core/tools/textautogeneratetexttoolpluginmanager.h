/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratepluginutils.h"
#include "textautogeneratetext_private_export.h"
#include <KPluginMetaData>
#include <QJsonArray>
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
    TextAutoGeneratePluginUtils::PluginUtilData pluginData;
    TextAutoGenerateTextToolPlugin *plugin = nullptr;
    bool isEnabled = true;
};

class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPluginManager final : public QObject
{
    Q_OBJECT
public:
    struct PluginToolInfo {
        QString displayName;
        QString description;
        QByteArray identifier;
    };
    ~TextAutoGenerateTextToolPluginManager() override;
    static TextAutoGenerateTextToolPluginManager *self();

    [[nodiscard]] QList<TextAutoGenerateTextToolPlugin *> pluginsList() const;

    [[nodiscard]] QString configGroupName() const;
    [[nodiscard]] QString configPrefixSettingKey() const;

    [[nodiscard]] QList<TextAutoGeneratePluginUtils::PluginUtilData> pluginDataList() const;

    [[nodiscard]] TextAutoGenerateTextToolPlugin *pluginFromIdentifier(const QString &identifier) const;

    [[nodiscard]] QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> activePluginTools() const;

    [[nodiscard]] QJsonArray generateToolsArray(const QList<QByteArray> &tools) const;

private:
    explicit TextAutoGenerateTextToolPluginManager(QObject *parent = nullptr);
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializePluginList();
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadPlugin(TextAutoGenerateTextToolPluginManagerInfo *item);
    QList<TextAutoGenerateTextToolPluginManagerInfo> mPluginList;
    QList<TextAutoGeneratePluginUtils::PluginUtilData> mPluginDataList;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextToolPluginManager::PluginToolInfo, Q_RELOCATABLE_TYPE);
