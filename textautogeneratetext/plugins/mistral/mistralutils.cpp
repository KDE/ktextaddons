/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mistralutils.h"

QString MistralUtils::modelsPath()
{
    return QStringLiteral("/v1/models");
}

QString MistralUtils::chatsPath()
{
    return QStringLiteral("/v1/chat/completions");
}
