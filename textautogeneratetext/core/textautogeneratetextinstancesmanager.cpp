/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanager.h"

#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextcore_debug.h"
#include "textautogeneratetextutils.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManager::TextAutoGenerateTextInstancesManager(TextAutoGenerateManager *manager, QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateTextInstanceModel(new TextAutoGenerateTextInstanceModel(this))
    , mTextAutoGenerateEngineLoader(new TextAutoGenerateEngineLoader(this))
    , mManager(manager)
{
}

TextAutoGenerateTextInstancesManager::~TextAutoGenerateTextInstancesManager()
{
}

bool TextAutoGenerateTextInstancesManager::isEmpty() const
{
    return mTextAutoGenerateTextInstanceModel->isEmpty();
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextInstancesManager::textAutoGeneratePlugin() const
{
    if (mTextAutoGenerateTextInstanceModel->isEmpty()) {
        return nullptr;
    }
    return mTextAutoGenerateTextInstanceModel->currentPlugin();
}

void TextAutoGenerateTextInstancesManager::loadInstances()
{
    auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::instanceConfigFileName());
    mTextAutoGenerateEngineLoader->loadPlugins();
    const QStringList instancesList = TextAutoGenerateTextUtils::instancesList(config);
    if (instancesList.isEmpty()) {
        return; // nothing to be done...
    }

    QList<TextAutoGenerateTextInstance *> lstInstances;
    for (const auto &group : instancesList) {
        const KConfigGroup configGroup(config, group);
        auto inst = new TextAutoGenerateTextInstance;
        inst->load(configGroup);

        auto client = mTextAutoGenerateEngineLoader->searchTextAutoGenerateTextClient(inst->pluginName());
        if (!client) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Impossible to create client " << inst->pluginName();
            delete inst;
        } else {
            auto plugin = client->createTextAutoGeneratePlugin(mManager, inst);
            plugin->load(configGroup);
            connect(plugin, &TextAutoGenerateTextPlugin::configChanged, this, &TextAutoGenerateTextInstancesManager::saveInstances);
            inst->setPlugin(plugin);
            lstInstances.append(inst);
        }
    }
    // qDebug() << " lstInstances " << lstInstances;
    setInstances(lstInstances);
    // Set current Instance after loading all instances. Otherwise we can'"t have default instance
    const KConfigGroup configGeneralGroup(config, u"General"_s);
    setCurrentinstance(configGeneralGroup.readEntry("currentInstance", QByteArray()));
}

void TextAutoGenerateTextInstancesManager::saveInstances()
{
    auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::instanceConfigFileName());
    KConfigGroup configGeneralGroup(config, u"General"_s);
    configGeneralGroup.writeEntry("currentInstance", currentInstance());

    const auto instanceList = TextAutoGenerateTextUtils::instancesList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    const QList<TextAutoGenerateTextInstance *> instanceLst = instances();
    for (int i = 0; i < instanceLst.count(); ++i) {
        KConfigGroup group = config->group(u"Instance #%1"_s.arg(i));
        instanceLst.at(i)->save(group);
    }
    config->sync();
}

TextAutoGenerateTextInstanceModel *TextAutoGenerateTextInstancesManager::textAutoGenerateTextInstanceModel() const
{
    return mTextAutoGenerateTextInstanceModel;
}

bool TextAutoGenerateTextInstancesManager::isCurrentInstance(const QByteArray &instanceUuid) const
{
    return currentInstance() == instanceUuid;
}

QStringList TextAutoGenerateTextInstancesManager::instanceDisplayNames() const
{
    return mTextAutoGenerateTextInstanceModel->instanceDisplayNames();
}

QList<TextAutoGenerateTextInstance *> TextAutoGenerateTextInstancesManager::instances() const
{
    return mTextAutoGenerateTextInstanceModel->textInstances();
}

void TextAutoGenerateTextInstancesManager::setInstances(const QList<TextAutoGenerateTextInstance *> &newInstances)
{
    mTextAutoGenerateTextInstanceModel->setTextInstances(newInstances);
}

void TextAutoGenerateTextInstancesManager::deleteInstance(const QByteArray &uuid)
{
    if (auto plugin = mTextAutoGenerateTextInstanceModel->removeInstance(uuid); plugin) {
        plugin->remove();
    }
}

void TextAutoGenerateTextInstancesManager::addInstance(TextAutoGenerateTextInstance *instance)
{
    mTextAutoGenerateTextInstanceModel->addInstance(instance);
}

QByteArray TextAutoGenerateTextInstancesManager::currentInstance() const
{
    return mTextAutoGenerateTextInstanceModel->currentInstance();
}

void TextAutoGenerateTextInstancesManager::setCurrentinstance(const QByteArray &newCurrentinstance)
{
    mTextAutoGenerateTextInstanceModel->setCurrentInstance(newCurrentinstance);
}

TextAutoGenerateEngineLoader *TextAutoGenerateTextInstancesManager::textAutoGenerateEngineLoader() const
{
    return mTextAutoGenerateEngineLoader;
}

#include "moc_textautogeneratetextinstancesmanager.cpp"
