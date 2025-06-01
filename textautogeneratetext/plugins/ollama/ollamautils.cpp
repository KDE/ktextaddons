/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamautils.h"

QString OllamaUtils::tagsPath()
{
    return QStringLiteral("/api/tags");
}

QString OllamaUtils::completionPath()
{
    return QStringLiteral("/api/generate");
}

QString OllamaUtils::pullPath()
{
    return QStringLiteral("/api/pull");
}

QString OllamaUtils::versionPath()
{
    return QStringLiteral("/api/version");
}

QString OllamaUtils::modelInfoPath()
{
    return QStringLiteral("/api/show");
}

QString OllamaUtils::chatPath()
{
    return QStringLiteral("/api/chat");
}

QString OllamaUtils::deletePath()
{
    return QStringLiteral("/api/delete");
}

QString OllamaUtils::createPath()
{
    return QStringLiteral("/api/create");
}
