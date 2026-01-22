/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemodelavailablelistview.h"
// #include "genericnetworkmodelavailableinfosdelegate.h"
using namespace TextAutoGenerateText;
TextAutoGenerateModelAvailableListView::TextAutoGenerateModelAvailableListView(QWidget *parent)
    : QListView(parent)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes

    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);

    // setItemDelegate(new GenericNetworkModelAvailableInfosDelegate(this));
}

TextAutoGenerateModelAvailableListView::~TextAutoGenerateModelAvailableListView() = default;

#include "moc_textautogeneratemodelavailablelistview.cpp"
