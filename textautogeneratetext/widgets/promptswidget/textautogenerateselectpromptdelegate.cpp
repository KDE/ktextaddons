/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectpromptdelegate.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSelectPromptDelegate::TextAutoGenerateSelectPromptDelegate(QObject *parent)
    : QItemDelegate{parent}
{
}

TextAutoGenerateSelectPromptDelegate::~TextAutoGenerateSelectPromptDelegate() = default;

#include "moc_textautogenerateselectpromptdelegate.cpp"
