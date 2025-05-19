/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessageutils.h"

using namespace TextAutoGenerateText;

QString TextAutoGenerateSearchMessageUtils::generatePreview(const QString &str)
{
    if (str.length() > 60) {
        return QStringLiteral("%1...").arg(str.right(60));
    }
    return str;
}
