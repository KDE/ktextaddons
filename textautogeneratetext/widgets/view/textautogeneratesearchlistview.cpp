/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchlistview.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratesearchlistviewdelegate.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchListView::TextAutoGenerateSearchListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QListView(parent)
    , mDelegate(new TextAutoGenerateSearchListViewDelegate(this))
    , mManager(manager)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes
    setItemDelegate(mDelegate);
    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);
}

TextAutoGenerateSearchListView::~TextAutoGenerateSearchListView() = default;

#include "moc_textautogeneratesearchlistview.cpp"
