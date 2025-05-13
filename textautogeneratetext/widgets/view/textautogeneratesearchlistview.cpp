/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchlistview.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchListView::TextAutoGenerateSearchListView(QWidget *parent)
    : QListView(parent)
{
}

TextAutoGenerateSearchListView::~TextAutoGenerateSearchListView() = default;

#include "moc_textautogeneratesearchlistview.cpp"
