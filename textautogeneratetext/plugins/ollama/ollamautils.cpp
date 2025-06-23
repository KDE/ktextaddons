/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamautils.h"
using namespace Qt::Literals::StringLiterals;

QString OllamaUtils::tagsPath()
{
    return u"/api/tags"_s;
}

QString OllamaUtils::completionPath()
{
    return u"/api/generate"_s;
}

QString OllamaUtils::pullPath()
{
    return u"/api/pull"_s;
}

QString OllamaUtils::versionPath()
{
    return u"/api/version"_s;
}

QString OllamaUtils::modelInfoPath()
{
    return u"/api/show"_s;
}

QString OllamaUtils::chatPath()
{
    return u"/api/chat"_s;
}

QString OllamaUtils::deletePath()
{
    return u"/api/delete"_s;
}

QString OllamaUtils::createPath()
{
    return u"/api/create"_s;
}
