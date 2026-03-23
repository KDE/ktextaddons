/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternalInterface
{
public:
    TextAutoGenerateTextToolInternalInterface();
    virtual ~TextAutoGenerateTextToolInternalInterface();

    virtual void execute() = 0;
};
}
