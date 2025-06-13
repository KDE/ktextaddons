/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanager.h"
#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/textautogenerateengineloader.h"

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
    // TODO
}

void TextAutoGenerateTextInstancesManager::saveInstances()
{
    // TODO
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
