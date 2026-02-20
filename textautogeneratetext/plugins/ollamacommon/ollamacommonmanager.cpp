/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmanager.h"

OllamaCommonManager::OllamaCommonManager(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
{
}

OllamaCommonManager::~OllamaCommonManager() = default;

bool OllamaCommonManager::hasVisionSupport(const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasToolsSupport(const QString &modelName) const

{
    return false;
}

bool OllamaCommonManager::hasOcrSupport(const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasAudioSupport(const QString &modelName) const
{
    return false;
}

bool OllamaCommonManager::hasThinkSupport(const QString &modelName) const
{
    return false;
}

#include "moc_ollamacommonmanager.cpp"
