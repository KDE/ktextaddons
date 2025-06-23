/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailablelistview.h"
#include "genericnetworkmodelavailableinfosdelegate.h"

GenericNetworkModelAvailableListView::GenericNetworkModelAvailableListView(QWidget *parent)
    : QListView(parent)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes

    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);

    setItemDelegate(new GenericNetworkModelAvailableInfosDelegate(this));
}

GenericNetworkModelAvailableListView::~GenericNetworkModelAvailableListView() = default;

#include "moc_genericnetworkmodelavailablelistview.cpp"
