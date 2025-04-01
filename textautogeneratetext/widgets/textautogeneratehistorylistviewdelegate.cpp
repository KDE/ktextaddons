/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistviewdelegate.h"

using namespace TextAutogenerateText;
TextAutogenerateHistoryListViewDelegate::TextAutogenerateHistoryListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

TextAutogenerateHistoryListViewDelegate::~TextAutogenerateHistoryListViewDelegate() = default;

#include "moc_textautogeneratehistorylistviewdelegate.cpp"
