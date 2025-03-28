/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistview.h"

using namespace TextAutogenerateText;
TextAutogenerateHistoryListView::TextAutogenerateHistoryListView(QWidget *parent)
    : QListView(parent)
{
}

TextAutogenerateHistoryListView::~TextAutogenerateHistoryListView() = default;

#include "moc_textautogeneratehistorylistview.cpp"
