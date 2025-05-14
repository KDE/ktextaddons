/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchlistviewdelegate.h"
#include <QListView>

using namespace TextAutoGenerateText;
TextAutoGenerateSearchListViewDelegate::TextAutoGenerateSearchListViewDelegate(QListView *view)
    : TextAutoGenerateListViewBaseDelegate{view}
{
}

TextAutoGenerateSearchListViewDelegate::~TextAutoGenerateSearchListViewDelegate() = default;

QTextDocument *TextAutoGenerateSearchListViewDelegate::documentForIndex(const QModelIndex &index, int width) const
{
    // TODO
    return nullptr;
}

#include "moc_textautogeneratesearchlistviewdelegate.cpp"
