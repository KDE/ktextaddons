/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistview.h"
#include "core/textautogeneratechatmodel.h"
#include "textautogeneratelistviewdelegate.h"

using namespace TextAutogenerateText;
TextAutogenerateListView::TextAutogenerateListView(QWidget *parent)
    : QListView(parent)
    , mTextAutoGenerateChatModel(new TextAutoGenerateChatModel(this))
{
    setItemDelegate(new TextAutogenerateListViewDelegate(this));
    setModel(mTextAutoGenerateChatModel);
}

TextAutogenerateListView::~TextAutogenerateListView() = default;

#include "moc_textautogeneratelistview.cpp"
