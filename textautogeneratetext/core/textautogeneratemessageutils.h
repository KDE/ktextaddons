/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextcore_export.h"
#include <QString>
namespace TextAutoGenerateText
{
/*!
 * \namespace TextAutoGenerateText::TextAutoGenerateMessageUtils
 * \inmodule TextAutoGenerateTextCore
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateMessageUtils
 */
namespace TextAutoGenerateMessageUtils
{
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QString convertTextToHtml(const QString &str,
                                                                        const QByteArray &uuid,
                                                                        const QString &searchedText,
                                                                        int &numberOfTextSearched,
                                                                        int hightLightStringIndex,
                                                                        bool allowInsertText);
}
}
