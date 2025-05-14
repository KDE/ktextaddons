/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchlistview.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratesearchmessagesmodel.h"
#include "textautogeneratesearchlistviewdelegate.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchListView::TextAutoGenerateSearchListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : TextAutoGenerateBaseListView(parent)
    , mDelegate(new TextAutoGenerateSearchListViewDelegate(this))
    , mManager(manager)
    , mModel(new TextAutoGenerateSearchMessagesModel(this))
{
    setItemDelegate(mDelegate);
    setModel(mModel);
}

TextAutoGenerateSearchListView::~TextAutoGenerateSearchListView() = default;

#include "moc_textautogeneratesearchlistview.cpp"
