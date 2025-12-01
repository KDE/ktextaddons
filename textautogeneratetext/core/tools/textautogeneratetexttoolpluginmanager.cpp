/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratetexttoolpluginmanager.h"

#include "textautogeneratetextcore_debug.h"
#include "textautogeneratetexttoolplugin.h"

#include <KLocalizedString>
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
    const TextAddonsWidgets::PluginUtil::PluginsStateList pair =
        TextAddonsWidgets::PluginUtil::loadPluginSetting({}, configGroupName(), configPrefixSettingKey());

    QListIterator<KPluginMetaData> i(plugins);
    i.toBack();
    QSet<QString> unique;
    while (i.hasPrevious()) {
        TextAutoGenerateTextToolPluginManagerInfo info;
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

    QList<TextAutoGenerateTextToolPluginManagerInfo> activePluginsList = mPluginList;
    std::sort(activePluginsList.begin(),
              activePluginsList.end(),
              [](const TextAutoGenerateTextToolPluginManagerInfo &left, const TextAutoGenerateTextToolPluginManagerInfo &right) {
                  return left.plugin->order() < right.plugin->order();
              });

    const QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator end(activePluginsList.constEnd());
    for (QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator it = activePluginsList.constBegin(); it != end; ++it) {
        if (auto plugin = (*it).plugin) {
            if (plugin->enabled()) {
                const TextAutoGenerateTextToolPluginManager::PluginToolInfo info{
                    .iconName = plugin->iconName(),
                    .displayName = plugin->displayName(),
                    .description = plugin->description(),
                    .identifier = plugin->toolNameId(),
                };
                list.append(info);
            }
        }
    }
    return list;
}

QList<TextAddonsWidgets::PluginUtilData> TextAutoGenerateTextToolPluginManager::pluginDataList() const
{
    return mPluginDataList;
}

TextAutoGenerateTextToolPlugin *TextAutoGenerateTextToolPluginManager::pluginFromToolNameId(const QByteArray &identifier) const
{
    const auto it = std::find_if(mPluginList.constBegin(), mPluginList.constEnd(), [identifier](const TextAutoGenerateTextToolPluginManagerInfo &info) {
        return info.plugin->toolNameId() == identifier;
    });
    if (it != mPluginList.end()) {
        return (*it).plugin;
    }
    return nullptr;
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

QJsonArray TextAutoGenerateTextToolPluginManager::generateToolsArray(const QList<QByteArray> &tools) const
{
    QJsonArray toolsArray;
    for (const QByteArray &t : tools) {
        bool toolFound = false;
        const QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator end(mPluginList.constEnd());
        for (QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
            if (it->plugin->toolNameId() == t) {
                toolsArray.append(it->plugin->metadata());
                toolFound = true;
                break;
            }
        }
        if (!toolFound) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Tool not found" << t;
        }
    }
    return toolsArray;
}

QString TextAutoGenerateTextToolPluginManager::convertIdentifierToDisplay(const QList<QByteArray> &tools) const
{
    QString toolDisplayList;
    for (const QByteArray &t : tools) {
        const QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator end(mPluginList.constEnd());
        for (QList<TextAutoGenerateTextToolPluginManagerInfo>::ConstIterator it = mPluginList.constBegin(); it != end; ++it) {
            if (it->plugin->toolNameId() == t) {
                toolDisplayList.append(u"<li>"_s + it->plugin->displayName() + u"</li>"_s);
                break;
            }
        }
    }
    return toolDisplayList;
}

QString TextAutoGenerateTextToolPluginManager::generatePluginsInformation() const
{
    QString result = i18n("Plugins Text:");
    const QString tab = u"   "_s;
    for (const auto &p : mPluginDataList) {
        result += u'\n';
        result += tab + p.mName + u'\n';
        result += tab + p.mDescription + u'\n';
        result += tab + i18n("Tool identifier: %1", p.mIdentifier) + u'\n';
        result += tab + i18n("Activate: %1", p.mEnableByDefault ? i18n("On") : i18n("Off")) + u'\n';
    }
    return result;
}

#include "moc_textautogeneratetexttoolpluginmanager.cpp"
