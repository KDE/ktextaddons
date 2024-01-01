/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextengineloader.h"
#include "speechtotextclient.h"
#include "textspeechtotext_debug.h"
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
using namespace TextSpeechToText;
class TextSpeechToText::SpeechToTextEngineLoaderPrivate
{
public:
    QSet<QString> loadedPlugins;
    QHash<QString, SpeechToTextClient *> speechToTextClients;
};

SpeechToTextEngineLoader *SpeechToTextEngineLoader::self()
{
    static SpeechToTextEngineLoader s_self;
    return &s_self;
}

SpeechToTextEngineLoader::SpeechToTextEngineLoader(QObject *parent)
    : QObject{parent}
    , d(new TextSpeechToText::SpeechToTextEngineLoaderPrivate)
{
    loadPlugins();
}

SpeechToTextEngineLoader::~SpeechToTextEngineLoader() = default;

void SpeechToTextEngineLoader::loadPlugins()
{
    const QStringList libPaths = QCoreApplication::libraryPaths();
    const QString pathSuffix(QStringLiteral("/kf" QT_STRINGIFY(QT_VERSION_MAJOR)) + QStringLiteral("/speechtotext/"));
    for (const QString &libPath : libPaths) {
        const QDir dir(libPath + pathSuffix);
        if (!dir.exists()) {
            continue;
        }
        for (const QString &fileName : dir.entryList(QDir::Files)) {
            loadPlugin(dir.absoluteFilePath(fileName));
        }
    }
    if (d->loadedPlugins.isEmpty()) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "No speechtotext plugins available!";
        Q_EMIT noPluginsFound();
    }
}

void SpeechToTextEngineLoader::loadPlugin(const QString &pluginPath)
{
    QPluginLoader plugin(pluginPath);
    const QString pluginIID = plugin.metaData()[QLatin1String("IID")].toString();
    if (!pluginIID.isEmpty()) {
        if (d->loadedPlugins.contains(pluginIID)) {
            qCDebug(TEXTSPEECHTOTEXT_LOG) << "Skipping already loaded" << pluginPath;
            return;
        }
        d->loadedPlugins.insert(pluginIID);
    }

    if (!plugin.load()) { // We do this separately for better error handling
        qCDebug(TEXTSPEECHTOTEXT_LOG) << "Unable to load plugin" << pluginPath << "Error:" << plugin.errorString();
        d->loadedPlugins.remove(pluginIID);
        return;
    }
    SpeechToTextClient *client = qobject_cast<SpeechToTextClient *>(plugin.instance());
    if (!client) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Invalid plugin loaded" << pluginPath;
        plugin.unload(); // don't leave it in memory
        return;
    }
    d->speechToTextClients.insert(client->name(), client);
}

SpeechToTextClient *SpeechToTextEngineLoader::createSpeechToTextClient(const QString &clientName)
{
    auto clientsItr = d->speechToTextClients.constFind(clientName);
    if (clientsItr == d->speechToTextClients.constEnd()) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Client name not found: " << clientName;
        Q_EMIT loadingSpeechToTextFailed();
        return nullptr;
    }
    return (*clientsItr);
}

bool SpeechToTextEngineLoader::hasConfigurationDialog(const QString &clientName) const
{
    auto clientsItr = d->speechToTextClients.constFind(clientName);
    if (clientsItr == d->speechToTextClients.constEnd()) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Client name not found: " << clientName;
        return false;
    }
    return (*clientsItr)->hasConfigurationDialog();
}

bool SpeechToTextEngineLoader::showConfigureDialog(const QString &clientName, QWidget *parentWidget)
{
    auto clientsItr = d->speechToTextClients.constFind(clientName);
    if (clientsItr == d->speechToTextClients.constEnd()) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Client name not found: " << clientName;
        return false;
    }
    return (*clientsItr)->showConfigureDialog(parentWidget);
}

QMap<QString, QString> SpeechToTextEngineLoader::speechToTextEngineInfos() const
{
    QMap<QString, QString> map;
    QHashIterator<QString, SpeechToTextClient *> i(d->speechToTextClients);
    while (i.hasNext()) {
        i.next();
        map.insert(i.key(), i.value()->translatedName());
    }
    return map;
}

QString SpeechToTextEngineLoader::fallbackFirstEngine() const
{
    if (!d->speechToTextClients.isEmpty()) {
        return *d->speechToTextClients.keyBegin();
    }
    qCWarning(TEXTSPEECHTOTEXT_LOG) << "No plugin found ! ";
    return QString();
}

bool SpeechToTextEngineLoader::hasEngine() const
{
    return !d->speechToTextClients.isEmpty();
}

#include "moc_speechtotextengineloader.cpp"
