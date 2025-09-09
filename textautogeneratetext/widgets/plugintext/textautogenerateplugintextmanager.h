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
class TextAutoGeneratePluginText;
class TextAutoGeneratePluginTextManagerInfo
{
public:
    TextAutoGeneratePluginTextManagerInfo() = default;

    KPluginMetaData data;
    QString metaDataFileNameBaseName;
    QString metaDataFileName;
    TextAutoGeneratePluginTextUtils::PluginUtilData pluginData;
    TextAutoGeneratePluginText *plugin = nullptr;
    bool isEnabled = true;
};

class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGeneratePluginTextManager final : public QObject
{
    Q_OBJECT
public:
    ~TextAutoGeneratePluginTextManager() override;
    static TextAutoGeneratePluginTextManager *self();

    [[nodiscard]] QList<TextAutoGeneratePluginText *> pluginsList() const;

    [[nodiscard]] QString configGroupName() const;
    [[nodiscard]] QString configPrefixSettingKey() const;

    [[nodiscard]] QList<TextAutoGeneratePluginTextUtils::PluginUtilData> pluginDataList() const;

    [[nodiscard]] TextAutoGeneratePluginText *pluginFromIdentifier(const QString &identifier) const;

private:
    explicit TextAutoGeneratePluginTextManager(QObject *parent = nullptr);
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializePluginList();
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadPlugin(TextAutoGeneratePluginTextManagerInfo *item);
    QList<TextAutoGeneratePluginTextManagerInfo> mPluginList;
    QList<TextAutoGeneratePluginTextUtils::PluginUtilData> mPluginDataList;
};
}
