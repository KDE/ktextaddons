/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonutils.h"
using namespace Qt::Literals::StringLiterals;

QString OllamaCommonUtils::tagsPath()
{
    return u"/api/tags"_s;
}

QString OllamaCommonUtils::completionPath()
{
    return u"/api/generate"_s;
}

QString OllamaCommonUtils::pullPath()
{
    return u"/api/pull"_s;
}

QString OllamaCommonUtils::versionPath()
{
    return u"/api/version"_s;
}

QString OllamaCommonUtils::modelInfoPath()
{
    return u"/api/show"_s;
}

QString OllamaCommonUtils::chatPath()
{
    return u"/api/chat"_s;
}

QString OllamaCommonUtils::deletePath()
{
    return u"/api/delete"_s;
}

QString OllamaCommonUtils::createPath()
{
    return u"/api/create"_s;
}
