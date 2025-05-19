/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessageutils.h"

using namespace TextAutoGenerateText;

QString TextAutoGenerateSearchMessageUtils::generatePreview(const QString &str)
{
    if (str.length() > 120) {
        return QStringLiteral("%1...").arg(str.left(120));
    }
    return str;
}

QString TextAutoGenerateSearchMessageUtils::generateGoToMessageLink(const QString &chatId, const QString &messageId)
{
    return QStringLiteral("storage://%1:%2").arg(chatId, messageId);
}
