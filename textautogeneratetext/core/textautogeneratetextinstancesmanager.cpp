/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanager.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManager::TextAutoGenerateTextInstancesManager(QObject *parent)
    : QObject{parent}
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

QList<TextAutoGenerateTextInstance> TextAutoGenerateTextInstancesManager::instances() const
{
    return mInstances;
}

void TextAutoGenerateTextInstancesManager::setInstances(const QList<TextAutoGenerateTextInstance> &newInstances)
{
    mInstances = newInstances;
}

void TextAutoGenerateTextInstancesManager::deleteInstance(const QByteArray &uuid)
{
    // TODO
}

void TextAutoGenerateTextInstancesManager::addInstance(const TextAutoGenerateTextInstance &instance)
{
    // TODO
}

#include "moc_textautogeneratetextinstancesmanager.cpp"
