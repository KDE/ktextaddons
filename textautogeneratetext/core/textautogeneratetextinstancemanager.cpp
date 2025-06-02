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

#include "moc_textautogeneratetextinstancemanager.cpp"
