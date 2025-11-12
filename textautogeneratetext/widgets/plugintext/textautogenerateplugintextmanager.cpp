/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogenerateplugintextmanager.h"

#include "textautogenerateplugintext.h"

#include <KPluginFactory>
#include <KPluginMetaData>
#include <QFileInfo>
#include <QSet>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGeneratePluginTextManager::TextAutoGeneratePluginTextManager(QObject *parent)
    : QObject(parent)
{
    initializePluginList();
}

TextAutoGeneratePluginTextManager::~TextAutoGeneratePluginTextManager() = default;

TextAutoGeneratePluginTextManager *TextAutoGeneratePluginTextManager::self()
{
    static TextAutoGeneratePluginTextManager s_self;
    return &s_self;
}

QString TextAutoGeneratePluginTextManager::configGroupName() const
{
    return u"autogeneratetext-textplugins"_s;
}

QString TextAutoGeneratePluginTextManager::configPrefixSettingKey() const
{
    return u"textpluginsPlugin"_s;
}

void TextAutoGeneratePluginTextManager::initializePluginList()
{
    const QList<KPluginMetaData> plugins = KPluginMetaData::findPlugins(u"autogeneratetext/textplugins"_s);
    const TextAddonsWidgets::PluginUtil::PluginsStateList pair =
        TextAddonsWidgets::PluginUtil::loadPluginSetting({}, configGroupName(), configPrefixSettingKey());

    QListIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        TextAutoGeneratePluginTextManagerInfo info;
        const KPluginMetaData data = i.previous();

        // 1) get plugin data => name/description etc.
        info.pluginData = TextAddonsWidgets::PluginUtil::createPluginMetaData(data);
        // 2) look at if plugin is activated
        const bool isPluginActivated = TextAddonsWidgets::PluginUtil::isPluginActivated(pair.enabledPluginList,
                                                                                        pair.disabledPluginList,
                                                                                        info.pluginData.mEnableByDefault,
                                                                                        info.pluginData.mIdentifier);
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
    QList<TextAutoGeneratePluginTextManagerInfo>::iterator end(mPluginList.end());
    for (QList<TextAutoGeneratePluginTextManagerInfo>::iterator it = mPluginList.begin(); it != end; ++it) {
        loadPlugin(&(*it));
    }
}

void TextAutoGeneratePluginTextManager::loadPlugin(TextAutoGeneratePluginTextManagerInfo *item)
{
    if (auto plugin =
            KPluginFactory::instantiatePlugin<TextAutoGeneratePluginText>(item->data, this, QVariantList() << item->metaDataFileNameBaseName).plugin) {
        item->plugin = plugin;
        item->plugin->setEnabled(item->isEnabled);
        item->pluginData.mHasConfigureDialog = item->plugin->hasConfigureDialog();
        mPluginDataList.append(item->pluginData);
    }
}

QList<TextAddonsWidgets::PluginUtilData> TextAutoGeneratePluginTextManager::pluginDataList() const
{
    return mPluginDataList;
}

TextAutoGeneratePluginText *TextAutoGeneratePluginTextManager::pluginFromIdentifier(const QString &identifier) const
{
    const auto it = std::find_if(mPluginList.constBegin(), mPluginList.constEnd(), [identifier](const TextAutoGeneratePluginTextManagerInfo &info) {
        return info.pluginData.mIdentifier == identifier;
    });
    if (it != mPluginList.end()) {
        return (*it).plugin;
    }
    return nullptr;
}

QList<TextAutoGeneratePluginText *> TextAutoGeneratePluginTextManager::pluginsList() const
{
    QList<TextAutoGeneratePluginText *> lst;
    lst.reserve(mPluginList.count());
    QList<TextAutoGeneratePluginTextManagerInfo>::ConstIterator end(mPluginList.constEnd());
    for (QList<TextAutoGeneratePluginTextManagerInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
        if (auto plugin = (*it).plugin) {
            lst << plugin;
        }
    }
    return lst;
}

#include "moc_textautogenerateplugintextmanager.cpp"
