/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistview.h"
#include "textautogeneratehistorylistviewdelegate.h"

using namespace TextAutogenerateText;
TextAutogenerateHistoryListView::TextAutogenerateHistoryListView(QWidget *parent)
    : QListView(parent)
{
    setDragEnabled(false);
    setUniformItemSizes(true);
    // Add delegate
    setItemDelegate(new TextAutogenerateHistoryListViewDelegate(this));
}

TextAutogenerateHistoryListView::~TextAutogenerateHistoryListView() = default;

#include "moc_textautogeneratehistorylistview.cpp"
