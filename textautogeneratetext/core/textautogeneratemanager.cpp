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

TextAutogenerateManager *TextAutogenerateManager::self()
{
    static TextAutogenerateManager s_self;
    return &s_self;
}

// TODO add loadSettings/saveSettings

#include "moc_textautogeneratemanager.cpp"
