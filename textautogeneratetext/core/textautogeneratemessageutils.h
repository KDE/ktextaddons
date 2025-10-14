/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateMessageUtils
{
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QString
convertTextToHtml(const QString &str, const QByteArray &uuid, const QString &searchedText, int &numberOfTextSearched, int hightLightStringIndex);
}
};
