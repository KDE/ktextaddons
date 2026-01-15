/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaonlineutils.h"
using namespace Qt::Literals::StringLiterals;

QString OllamaOnlineUtils::tagsPath()
{
    return u"/api/tags"_s;
}

QString OllamaOnlineUtils::completionPath()
{
    return u"/api/generate"_s;
}

QString OllamaOnlineUtils::pullPath()
{
    return u"/api/pull"_s;
}

QString OllamaOnlineUtils::versionPath()
{
    return u"/api/version"_s;
}

QString OllamaOnlineUtils::modelInfoPath()
{
    return u"/api/show"_s;
}

QString OllamaOnlineUtils::chatPath()
{
    return u"/api/chat"_s;
}

QString OllamaOnlineUtils::deletePath()
{
    return u"/api/delete"_s;
}

QString OllamaOnlineUtils::createPath()
{
    return u"/api/create"_s;
}
