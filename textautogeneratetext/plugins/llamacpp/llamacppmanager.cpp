/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "llamacppmanager.h"

LLamaCppManager::LLamaCppManager(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
{
}

LLamaCppManager::~LLamaCppManager() = default;

void LLamaCppManager::loadModels()
{
    // TODO
}

TextAutoGenerateText::TextAutoGenerateReply *LLamaCppManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    // TODO
    return {};
}

TextAutoGenerateText::TextAutoGenerateReply *LLamaCppManager::getResponses(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    // TODO
    return {};
}
