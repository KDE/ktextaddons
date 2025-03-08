/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewdelegate.h"

using namespace TextAutogenerateText;
TextAutogenerateListViewDelegate::TextAutogenerateListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

TextAutogenerateListViewDelegate::~TextAutogenerateListViewDelegate() = default;
