/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewmessagebasedelegate.h"

using namespace TextAutoGenerateText;
TextAutoGenerateListViewMessageBaseDelegate::TextAutoGenerateListViewMessageBaseDelegate(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                         QListView *view)
    : TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate(manager, view)
{
}

TextAutoGenerateListViewMessageBaseDelegate::~TextAutoGenerateListViewMessageBaseDelegate() = default;
