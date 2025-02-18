/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"

using namespace TextAutogenerateText;
TextAutogenerateManager::TextAutogenerateManager(QObject *parent)
    : QObject{parent}
{
}

TextAutogenerateManager::~TextAutogenerateManager() = default;

#include "moc_textautogeneratemanager.cpp"
