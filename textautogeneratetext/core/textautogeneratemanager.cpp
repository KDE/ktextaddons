/*
SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratehistorymodel.h"

using namespace TextAutogenerateText;
TextAutogenerateManager::TextAutogenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateChatModel(new TextAutoGenerateChatModel(this))
    , mTextAutoGenerateHistoryModel(new TextAutoGenerateHistoryModel(this))
{
}

TextAutogenerateManager::~TextAutogenerateManager() = default;

TextAutogenerateManager *TextAutogenerateManager::self()
{
    static TextAutogenerateManager s_self;
    return &s_self;
}

TextAutoGenerateChatModel *TextAutogenerateManager::textAutoGenerateChatModel() const
{
    return mTextAutoGenerateChatModel;
}

void TextAutogenerateManager::loadHistory()
{
}

void TextAutogenerateManager::saveHistory()
{
}

TextAutoGenerateHistoryModel *TextAutogenerateManager::textAutoGenerateHistoryModel() const
{
    return mTextAutoGenerateHistoryModel;
}

#include "moc_textautogeneratemanager.cpp"
