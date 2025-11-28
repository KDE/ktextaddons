/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineloader.h"

#include "textautogeneratetextcore_debug.h"
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
class TextAutoGenerateText::TextAutoGenerateEngineLoaderPrivate
{
public:
    QSet<QString> loadedPlugins;
    QHash<QString, TextAutoGenerateTextClient *> autogenerateTextClients;
};

TextAutoGenerateEngineLoader::TextAutoGenerateEngineLoader(QObject *parent)
    : QObject{parent}
    , d(new TextAutoGenerateText::TextAutoGenerateEngineLoaderPrivate)
{
}

TextAutoGenerateEngineLoader::~TextAutoGenerateEngineLoader() = default;

void TextAutoGenerateEngineLoader::loadPlugins()
{
    // Already loaded
    if (!d->loadedPlugins.isEmpty()) {
        return;
    }
    const QStringList libPaths = QCoreApplication::libraryPaths();
    const QString pathSuffix(u"/kf6/textautogeneratetext/"_s);
    for (const QString &libPath : libPaths) {
        const QDir dir(libPath + pathSuffix);
        if (!dir.exists()) {
            continue;
        }
        const auto files = dir.entryList(QDir::Files);
        for (const QString &fileName : files) {
            loadPlugin(dir.absoluteFilePath(fileName));
        }
    }
    if (d->loadedPlugins.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "No autogenerate plugins available!";
        Q_EMIT noPluginsFound();
    }
}

void TextAutoGenerateEngineLoader::loadPlugin(const QString &pluginPath)
{
    QPluginLoader plugin(pluginPath);
    const QString pluginIID = plugin.metaData().value("IID"_L1).toString();
    if (!pluginIID.isEmpty()) {
        if (d->loadedPlugins.contains(pluginIID)) {
            qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "Skipping already loaded" << pluginPath;
            return;
        }
        d->loadedPlugins.insert(pluginIID);
    }

    if (!plugin.load()) { // We do this separately for better error handling
        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "Unable to load plugin" << pluginPath << "Error:" << plugin.errorString();
        d->loadedPlugins.remove(pluginIID);
        return;
    }
    TextAutoGenerateTextClient *client = qobject_cast<TextAutoGenerateTextClient *>(plugin.instance());
    if (!client) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid plugin loaded" << pluginPath;
        plugin.unload(); // don't leave it in memory
        return;
    }
    d->autogenerateTextClients.insert(client->name(), client);
}

TextAutoGenerateTextClient *TextAutoGenerateEngineLoader::searchTextAutoGenerateTextClient(const QString &clientName)
{
    auto clientsItr = d->autogenerateTextClients.constFind(clientName);
    if (clientsItr == d->autogenerateTextClients.constEnd()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Client name not found: " << clientName;
        Q_EMIT loadingPluginFailed();
        return nullptr;
    }
    return (*clientsItr);
}

QList<TextAutoGenerateTextClient::SupportedServer> TextAutoGenerateEngineLoader::supportedServers() const
{
    QList<TextAutoGenerateTextClient::SupportedServer> lst;
    QHashIterator<QString, TextAutoGenerateTextClient *> i(d->autogenerateTextClients);
    while (i.hasNext()) {
        i.next();
        lst += i.value()->supportedServers();
    }
    std::sort(lst.begin(), lst.end(), [](const TextAutoGenerateTextClient::SupportedServer &r, const TextAutoGenerateTextClient::SupportedServer &l) {
        return r.localizedName < l.localizedName;
    });

    return lst;
}

bool TextAutoGenerateEngineLoader::hasEngine() const
{
    return !d->autogenerateTextClients.isEmpty();
}

#include "moc_textautogenerateengineloader.cpp"
