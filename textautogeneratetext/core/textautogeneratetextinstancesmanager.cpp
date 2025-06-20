/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanager.h"
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
    return QStringLiteral("autogeneratetextinstances");
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

    KConfigGroup configGeneralGroup(config, QStringLiteral("General"));
    setCurrentinstance(configGeneralGroup.readEntry("currentInstance", QByteArray()));

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
            auto plugin = client->createTextAutoGeneratePlugin(mManager, inst->pluginIdentifier());
            plugin->load(configGroup);
            connect(plugin, &TextAutoGenerateTextPlugin::configChanged, this, &TextAutoGenerateTextInstancesManager::saveInstances);
            inst->setPlugin(plugin);
            lstInstances.append(inst);
        }
    }
    qDebug() << " lstInstances " << lstInstances;
    setInstances(lstInstances);
}

QStringList TextAutoGenerateTextInstancesManager::groupList(KConfig *config) const
{
    static const QRegularExpression regExpr(QStringLiteral("^Instance #\\d+$"));
    return config->groupList().filter(regExpr);
}

void TextAutoGenerateTextInstancesManager::saveInstances()
{
    auto config = new KConfig(configFileName());

    KConfigGroup configGeneralGroup(config, QStringLiteral("General"));
    configGeneralGroup.writeEntry("currentInstance", currentInstance());

    const auto instanceList = groupList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    const QList<TextAutoGenerateTextInstance *> instanceLst = instances();
    for (int i = 0; i < instanceLst.count(); ++i) {
        KConfigGroup group = config->group(QStringLiteral("Instance #%1").arg(i));
        instanceLst.at(i)->save(group);
    }
    config->sync();
}

TextAutoGenerateTextInstanceModel *TextAutoGenerateTextInstancesManager::textAutoGenerateTextInstanceModel() const
{
    return mTextAutoGenerateTextInstanceModel;
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
    mTextAutoGenerateTextInstanceModel->removeInstance(uuid);
}

void TextAutoGenerateTextInstancesManager::addInstance(TextAutoGenerateTextInstance *instance)
{
    mTextAutoGenerateTextInstanceModel->addTextInstances(instance);
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
