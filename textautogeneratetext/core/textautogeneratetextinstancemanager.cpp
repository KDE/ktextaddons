/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancemanager.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceManager::TextAutoGenerateTextInstanceManager(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextInstanceManager::~TextAutoGenerateTextInstanceManager() = default;

void TextAutoGenerateTextInstanceManager::loadInstances()
{
    // TODO
}

void TextAutoGenerateTextInstanceManager::saveInstances()
{
    // TODO
}

QList<TextAutoGenerateTextInstance> TextAutoGenerateTextInstanceManager::instances() const
{
    return mInstances;
}

void TextAutoGenerateTextInstanceManager::setInstances(const QList<TextAutoGenerateTextInstance> &newInstances)
{
    mInstances = newInstances;
}

#include "moc_textautogeneratetextinstancemanager.cpp"
