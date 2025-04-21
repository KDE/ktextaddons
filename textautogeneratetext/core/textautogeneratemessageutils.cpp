/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessageutils.h"
#include <KTextToHTML>

QString TextAutogenerateText::TextAutoGenerateMessageUtils::convertTextToHtml(const QString &str)
{
    const KTextToHTML::Options convertFlags = KTextToHTML::HighlightText | KTextToHTML::ConvertPhoneNumbers;
    return KTextToHTML::convertToHtml(str, convertFlags);
}
