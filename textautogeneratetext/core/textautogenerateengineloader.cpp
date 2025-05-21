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
    qDebug() << " void TextAutoGenerateEngineLoader::loadPlugins()*******";
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

void TextAutoGenerateEngineLoader::loadPlugin(const QString &pluginPath)
{
    QPluginLoader plugin(pluginPath);
    const QString pluginIID = plugin.metaData()["IID"_L1].toString();
    qDebug() << "pluginPath  " << pluginPath << " pluginIID " << pluginIID;
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

TextAutoGenerateTextClient *TextAutoGenerateEngineLoader::createTextAutoGenerateTextClient(const QString &clientName)
{
    auto clientsItr = d->autogenerateTextClients.constFind(clientName);
    if (clientsItr == d->autogenerateTextClients.constEnd()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Client name not found: " << clientName;
        Q_EMIT loadingPluginFailed();
        return nullptr;
    }
    return (*clientsItr);
}

bool TextAutoGenerateEngineLoader::hasConfigurationDialog(const QString &clientName) const
{
    auto clientsItr = d->autogenerateTextClients.constFind(clientName);
    if (clientsItr == d->autogenerateTextClients.constEnd()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Client name not found: " << clientName;
        return false;
    }
    return (*clientsItr)->hasConfigurationDialog();
}

bool TextAutoGenerateEngineLoader::showConfigureDialog(const QString &clientName, QWidget *parentWidget)
{
    auto clientsItr = d->autogenerateTextClients.constFind(clientName);
    if (clientsItr == d->autogenerateTextClients.constEnd()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Client name not found: " << clientName;
        return false;
    }
    return (*clientsItr)->showConfigureDialog(parentWidget);
}

QMap<QString, QString> TextAutoGenerateEngineLoader::textAutoGenerateTextEngineInfos() const
{
    QMap<QString, QString> map;
    QHashIterator<QString, TextAutoGenerateTextClient *> i(d->autogenerateTextClients);
    while (i.hasNext()) {
        i.next();
        map.insert(i.key(), generateDisplayName(i.value()));
    }
    return map;
}

QString TextAutoGenerateEngineLoader::generateDisplayName(TextAutoGenerateTextClient *client) const
{
    QString translatedName = client->translatedName();
    if (const QString modelName = client->modelName(); !modelName.isEmpty()) {
        translatedName += QStringLiteral(" (%1: %2)").arg(client->convertEngineType(client->engineType()), modelName);
    } else {
        translatedName += QStringLiteral(" (%1)").arg(client->convertEngineType(client->engineType()));
    }
    return translatedName;
}

QString TextAutoGenerateEngineLoader::website(TextAutoGenerateTextClient *client) const
{
    return client->webSite();
}

QString TextAutoGenerateEngineLoader::fallbackFirstEngine() const
{
    if (!d->autogenerateTextClients.isEmpty()) {
        return *d->autogenerateTextClients.keyBegin();
    }
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "No plugin found ! ";
    return QString();
}

bool TextAutoGenerateEngineLoader::hasEngine() const
{
    return !d->autogenerateTextClients.isEmpty();
}

#include "moc_textautogenerateengineloader.cpp"
