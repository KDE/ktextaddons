/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledlistview.h"
#include "ollamamodelavailableinfosdelegate.h"

OllamaModelInstalledListView::OllamaModelInstalledListView(QWidget *parent)
    : QListView(parent)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes

    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);

    setItemDelegate(new OllamaModelAvailableInfosDelegate(this));
}

OllamaModelInstalledListView::~OllamaModelInstalledListView() = default;

#include "moc_ollamamodelinstalledlistview.cpp"
