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
