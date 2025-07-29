/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanager.h"
using namespace Qt::Literals::StringLiterals;

#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/textautogenerateengineloader.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextcore_debug.h"
#include <KConfig>
#include <KConfigGroup>
#include <QRegularExpression>

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManager::TextAutoGenerateTextInstancesManager(TextAutoGenerateManager *manager, QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateTextInstanceModel(new TextAutoGenerateTextInstanceModel(this))
    , mTextAutoGenerateEngineLoader(new TextAutoGenerateEngineLoader(this))
    , mManager(manager)
{
}

TextAutoGenerateTextInstancesManager::~TextAutoGenerateTextInstancesManager() = default;

QString TextAutoGenerateTextInstancesManager::configFileName() const
{
    return u"autogeneratetextinstances"_s;
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
    mTextAutoGenerateEngineLoader->loadPlugins();
    auto config = new KConfig(configFileName());
    const QStringList instances = groupList(config);
    if (instances.isEmpty()) {
        return; // nothing to be done...
    }

    KConfigGroup configGeneralGroup(config, u"General"_s);

    QList<TextAutoGenerateTextInstance *> lstInstances;
    const auto instanceList = groupList(config);
    for (const auto &group : instanceList) {
        KConfigGroup configGroup(config, group);
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
    setCurrentinstance(configGeneralGroup.readEntry("currentInstance", QByteArray()));
}

QStringList TextAutoGenerateTextInstancesManager::groupList(KConfig *config) const
{
    static const QRegularExpression regExpr(u"^Instance #\\d+$"_s);
    return config->groupList().filter(regExpr);
}

void TextAutoGenerateTextInstancesManager::saveInstances()
{
    auto config = new KConfig(configFileName());

    KConfigGroup configGeneralGroup(config, u"General"_s);
    configGeneralGroup.writeEntry("currentInstance", currentInstance());

    const auto instanceList = groupList(config);
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
