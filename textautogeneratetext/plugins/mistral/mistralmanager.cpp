/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralmanager.h"
#include "core/textautogenerateengineaccessmanager.h"

MistralManager::MistralManager(QObject *parent)
    : QObject{parent}
{
}

MistralManager::~MistralManager() = default;

void MistralManager::loadModels()
{
    // TODO
}

#include "moc_mistralmanager.cpp"
