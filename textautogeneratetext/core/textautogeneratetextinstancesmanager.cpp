/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanager.h"
#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/textautogenerateengineloader.h"
#include <KConfig>
#include <KConfigGroup>
#include <QRegularExpression>

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManager::TextAutoGenerateTextInstancesManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateTextInstanceModel(new TextAutoGenerateTextInstanceModel(this))
    , mTextAutoGenerateEngineLoader(new TextAutoGenerateEngineLoader(this))
{
}

TextAutoGenerateTextInstancesManager::~TextAutoGenerateTextInstancesManager() = default;

void TextAutoGenerateTextInstancesManager::loadInstances()
{
    auto config = new KConfig(QStringLiteral("autogeneratetext"));
    const QStringList instances = groupList(config);
    if (instances.isEmpty()) {
        return; // nothing to be done...
    }

    KConfigGroup configGeneralGroup(config, QStringLiteral("General"));
    mCurrentinstance = configGeneralGroup.readEntry("currentInstance", QByteArray());

    QList<TextAutoGenerateTextInstance *> lstInstances;
    const auto instanceList = groupList(config);
    for (const auto &group : instanceList) {
        KConfigGroup configGroup(config, group);
        TextAutoGenerateTextInstance *inst = new TextAutoGenerateTextInstance;
        inst->load(configGroup);
        lstInstances.append(inst);
    }
    setInstances(lstInstances);
}

QStringList TextAutoGenerateTextInstancesManager::groupList(KConfig *config) const
{
    static const QRegularExpression regExpr(QStringLiteral("^Instance #\\d+$"));
    return config->groupList().filter(regExpr);
}

void TextAutoGenerateTextInstancesManager::saveInstances()
{
    auto config = new KConfig(QStringLiteral("autogeneratetext"));

    KConfigGroup configGeneralGroup(config, QStringLiteral("General"));
    configGeneralGroup.writeEntry("currentInstance", mCurrentinstance);

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
    return mCurrentinstance;
}

void TextAutoGenerateTextInstancesManager::setCurrentinstance(const QByteArray &newCurrentinstance)
{
    mCurrentinstance = newCurrentinstance;
}

TextAutoGenerateEngineLoader *TextAutoGenerateTextInstancesManager::textAutoGenerateEngineLoader() const
{
    return mTextAutoGenerateEngineLoader;
}

#include "moc_textautogeneratetextinstancesmanager.cpp"
