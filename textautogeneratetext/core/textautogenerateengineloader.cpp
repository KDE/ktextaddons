/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineloader.h"

#include "textautogeneratetextclient.h"
#include "textautogeneratetextcore_debug.h"
#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutogenerateText;
class TextAutogenerateText::TextAutogenerateEngineLoaderPrivate
{
public:
    QSet<QString> loadedPlugins;
    QHash<QString, TextAutogenerateTextClient *> autogenerateTextClients;
};

TextAutogenerateEngineLoader *TextAutogenerateEngineLoader::self()
{
    static TextAutogenerateEngineLoader s_self;
    return &s_self;
}

TextAutogenerateEngineLoader::TextAutogenerateEngineLoader(QObject *parent)
    : QObject{parent}
    , d(new TextAutogenerateText::TextAutogenerateEngineLoaderPrivate)
{
    loadPlugins();
}

TextAutogenerateEngineLoader::~TextAutogenerateEngineLoader() = default;

void TextAutogenerateEngineLoader::loadPlugins()
{
    const QStringList libPaths = QCoreApplication::libraryPaths();
    const QString pathSuffix(QStringLiteral("/kf6/textautogeneratetext/"));
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
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "No autogenerate plugins available!";
        Q_EMIT noPluginsFound();
    }
}

void TextAutogenerateEngineLoader::loadPlugin(const QString &pluginPath)
{
    QPluginLoader plugin(pluginPath);
    const QString pluginIID = plugin.metaData()["IID"_L1].toString();
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
    TextAutogenerateTextClient *client = qobject_cast<TextAutogenerateTextClient *>(plugin.instance());
    if (!client) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid plugin loaded" << pluginPath;
        plugin.unload(); // don't leave it in memory
        return;
    }
    d->autogenerateTextClients.insert(client->name(), client);
}

TextAutogenerateTextClient *TextAutogenerateEngineLoader::createTextAutoGenerateTextClient(const QString &clientName)
{
    auto clientsItr = d->autogenerateTextClients.constFind(clientName);
    if (clientsItr == d->autogenerateTextClients.constEnd()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Client name not found: " << clientName;
        Q_EMIT loadingPluginFailed();
        return nullptr;
    }
    return (*clientsItr);
}

bool TextAutogenerateEngineLoader::hasConfigurationDialog(const QString &clientName) const
{
    auto clientsItr = d->autogenerateTextClients.constFind(clientName);
    if (clientsItr == d->autogenerateTextClients.constEnd()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Client name not found: " << clientName;
        return false;
    }
    return (*clientsItr)->hasConfigurationDialog();
}

bool TextAutogenerateEngineLoader::showConfigureDialog(const QString &clientName, QWidget *parentWidget)
{
    auto clientsItr = d->autogenerateTextClients.constFind(clientName);
    if (clientsItr == d->autogenerateTextClients.constEnd()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Client name not found: " << clientName;
        return false;
    }
    return (*clientsItr)->showConfigureDialog(parentWidget);
}

QMap<QString, QString> TextAutogenerateEngineLoader::textAutoGenerateTextEngineInfos() const
{
    QMap<QString, QString> map;
    QHashIterator<QString, TextAutogenerateTextClient *> i(d->autogenerateTextClients);
    while (i.hasNext()) {
        i.next();
        map.insert(i.key(), generateDisplayName(i.value()));
    }
    return map;
}

QString TextAutogenerateEngineLoader::generateDisplayName(TextAutogenerateTextClient *client) const
{
    QString translatedName = client->translatedName();
    if (const QString modelName = client->modelName(); !modelName.isEmpty()) {
        translatedName += QStringLiteral(" (%1: %2)").arg(client->convertEngineType(client->engineType()), modelName);
    } else {
        translatedName += QStringLiteral(" (%1)").arg(client->convertEngineType(client->engineType()));
    }
    return translatedName;
}

QString TextAutogenerateEngineLoader::fallbackFirstEngine() const
{
    if (!d->autogenerateTextClients.isEmpty()) {
        return *d->autogenerateTextClients.keyBegin();
    }
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "No plugin found ! ";
    return QString();
}

bool TextAutogenerateEngineLoader::hasEngine() const
{
    return !d->autogenerateTextClients.isEmpty();
}

#include "moc_textautogenerateengineloader.cpp"
