/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratebaselistview.h"

using namespace TextAutoGenerateText;
TextAutoGenerateBaseListView::TextAutoGenerateBaseListView(QWidget *parent)
    : QListView(parent)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes

    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);
}

TextAutoGenerateBaseListView::~TextAutoGenerateBaseListView() = default;

#include "moc_textautogeneratebaselistview.cpp"
