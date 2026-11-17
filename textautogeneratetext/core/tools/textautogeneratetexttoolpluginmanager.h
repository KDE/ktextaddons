/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextcore_export.h"
#include <KPluginMetaData>
#include <QJsonArray>
#include <QList>
#include <QObject>
#include <TextAddonsCore/PluginUtil>

namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolPlugin;
class TextAutoGenerateManager;
class TextAutoGenerateTextToolPluginManagerInfo
{
public:
    TextAutoGenerateTextToolPluginManagerInfo() = default;

    KPluginMetaData data;
    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    TextAddonsCore::PluginUtilData pluginData;
    TextAutoGenerateTextToolPlugin *plugin = nullptr;
    bool isEnabled = true;
};
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolPluginManager
 * \brief The TextAutoGenerateTextToolPluginManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolPluginManager
 */
class TEXTAUTOGENERATETEXTCORE_EXPORT TextAutoGenerateTextToolPluginManager final : public QObject
{
    Q_OBJECT
public:
    struct PluginToolInfo {
        QString iconName;
        QString displayName;
        QString description;
        QByteArray identifier;
    };
    /*!
     */
    ~TextAutoGenerateTextToolPluginManager() override;
    /*!
     */
    static TextAutoGenerateTextToolPluginManager *self();

    /*!
     */
    [[nodiscard]] QString configGroupName() const;
    /*!
     */
    [[nodiscard]] QString configPrefixSettingKey() const;

    /*!
     */
    [[nodiscard]] QList<TextAddonsCore::PluginUtilData> pluginDataList() const;

    /*!
     */
    [[nodiscard]] TextAutoGenerateTextToolPlugin *pluginFromIdentifier(const QString &identifier) const;
    /*!
     */
    [[nodiscard]] TextAutoGenerateTextToolPlugin *pluginFromToolNameId(const QByteArray &identifier) const;

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> activePluginTools() const;

    /*!
     */
    [[nodiscard]] QJsonArray generateToolsArray(const QList<QByteArray> &tools) const;

    /*!
     */
    [[nodiscard]] QString convertIdentifierToDisplay(const QList<QByteArray> &tools) const;

    /*!
     */
    [[nodiscard]] QString generatePluginsInformation() const;

    /*!
     */
    [[nodiscard]] bool contains(const QByteArray &toolNameId) const;

    /*!
     */
    [[nodiscard]] TextAutoGenerateManager *manager() const;
    /*!
     */
    void setManager(TextAutoGenerateManager *newManager);

    /*!
     */
    [[nodiscard]] QJsonArray internalToolsMetaData() const;

private:
    TEXTAUTOGENERATETEXTCORE_NO_EXPORT explicit TextAutoGenerateTextToolPluginManager(QObject *parent = nullptr);
    TEXTAUTOGENERATETEXTCORE_NO_EXPORT void initializePluginList();
    TEXTAUTOGENERATETEXTCORE_NO_EXPORT void loadPlugin(TextAutoGenerateTextToolPluginManagerInfo *item);
    QList<TextAutoGenerateTextToolPluginManagerInfo> mPluginList;
    QList<TextAddonsCore::PluginUtilData> mPluginDataList;
    TextAutoGenerateManager *mManager = nullptr;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextToolPluginManager::PluginToolInfo, Q_RELOCATABLE_TYPE);
