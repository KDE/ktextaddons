/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratetexttoolpluginmanager.h"

#include "textautogeneratetexttoolplugin.h"

#include <KPluginFactory>
#include <KPluginMetaData>
#include <QFileInfo>
#include <QSet>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextToolPluginManager::TextAutoGenerateTextToolPluginManager(QObject *parent)
    : QObject(parent)
{
    initializePluginList();
}

TextAutoGenerateTextToolPluginManager::~TextAutoGenerateTextToolPluginManager() = default;

TextAutoGenerateTextToolPluginManager *TextAutoGenerateTextToolPluginManager::self()
{
    static TextAutoGenerateTextToolPluginManager s_self;
    return &s_self;
}

QString TextAutoGenerateTextToolPluginManager::configGroupName() const
{
    return u"autogeneratetext-toolplugins"_s;
}

QString TextAutoGenerateTextToolPluginManager::configPrefixSettingKey() const
{
    return u"toolplugins"_s;
}

void TextAutoGenerateTextToolPluginManager::initializePluginList()
{
    const QList<KPluginMetaData> plugins = KPluginMetaData::findPlugins(u"autogeneratetext/toolplugins"_s);
    const QPair<QStringList, QStringList> pair = TextAutoGeneratePluginUtils::loadPluginSetting(configGroupName(), configPrefixSettingKey());

    QListIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        TextAutoGenerateTextToolPluginManagerInfo info;
        const KPluginMetaData data = i.previous();

        // 1) get plugin data => name/description etc.
        info.pluginData = TextAutoGeneratePluginUtils::createPluginMetaData(data);
        // 2) look at if plugin is activated
        const bool isPluginActivated =
            TextAutoGeneratePluginUtils::isPluginActivated(pair.first, pair.second, info.pluginData.mEnableByDefault, info.pluginData.mIdentifier);
        info.isEnabled = isPluginActivated;
        info.metaDataFileNameBaseName = QFileInfo(data.fileName()).baseName();
        info.metaDataFileName = data.fileName();
        info.data = data;
        // only load plugins once, even if found multiple times!
        if (unique.contains(info.metaDataFileNameBaseName)) {
            continue;
        }
        info.plugin = nullptr;
        mPluginList.push_back(info);
        unique.insert(info.metaDataFileNameBaseName);
    }
    const QList<TextAutoGenerateTextToolPluginManagerInfo>::iterator end(mPluginList.end());
    for (QList<TextAutoGenerateTextToolPluginManagerInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
}

void TextAutoGenerateTextToolPluginManager::loadPlugin(TextAutoGenerateTextToolPluginManagerInfo *item)
{
    if (auto plugin =
            KPluginFactory::instantiatePlugin<TextAutoGenerateTextToolPlugin>(item->data, this, QVariantList() << item->metaDataFileNameBaseName).plugin) {
        item->plugin = plugin;
        item->plugin->setEnabled(item->isEnabled);
        item->pluginData.mHasConfigureDialog = true;
        mPluginDataList.append(item->pluginData);
    }
}

QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> TextAutoGenerateTextToolPluginManager::activePluginTools() const
{
    QList<TextAutoGenerateTextToolPluginManager::PluginToolInfo> list;
    const QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator end(mPluginList.constEnd());
    for (QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if (auto plugin = (*it).plugin) {
            const TextAutoGenerateTextToolPluginManager::PluginToolInfo info{.displayName = plugin->displayName(), .identifier = plugin->toolNameId()};
            list.append(info);
        }
    }
    return list;
}

QList<TextAutoGeneratePluginUtils::PluginUtilData> TextAutoGenerateTextToolPluginManager::pluginDataList() const
{
    return mPluginDataList;
}

TextAutoGenerateTextToolPlugin *TextAutoGenerateTextToolPluginManager::pluginFromIdentifier(const QString &identifier) const
{
    const auto it = std::find_if(mPluginList.constBegin(), mPluginList.constEnd(), [identifier](const TextAutoGenerateTextToolPluginManagerInfo &info) {
        return info.pluginData.mIdentifier == identifier;
    });
    if (it != mPluginList.end()) {
        return (*it).plugin;
    }
    return nullptr;
}

QList<TextAutoGenerateTextToolPlugin *> TextAutoGenerateTextToolPluginManager::pluginsList() const
{
    QList<TextAutoGenerateTextToolPlugin *> lst;
    lst.reserve(mPluginList.count());
    const QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator end(mPluginList.constEnd());
    for (QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if (auto plugin = (*it).plugin) {
            lst << plugin;
        }
    }
    return lst;
}

#include "moc_textautogeneratetexttoolpluginmanager.cpp"
