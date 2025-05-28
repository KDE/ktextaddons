/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mistralutils.h"

QString MistralUtils::modelsPath()
{
    return QStringLiteral("/v1/models");
}

QString MistralUtils::chatPath()
{
    return QStringLiteral("/v1/chat/completions");
}

QString MistralUtils::mistralAiUrl()
{
    return QStringLiteral("https://api.mistral.ai");
}

QString MistralUtils::mistralGroupName()
{
    return QStringLiteral("MistralAI");
}

QString MistralUtils::apiGroupName()
{
    return QStringLiteral("apiKey");
}
