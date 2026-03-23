/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty
 * \brief The TextAutoGenerateTextToolInternalProperty class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolInternalProperty
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternalProperty
{
public:
    TextAutoGenerateTextToolInternalProperty();
    ~TextAutoGenerateTextToolInternalProperty();
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty &t);
