/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodellistview.h"
#include "ollamamodelinfosdelegate.h"

OllamaModelListView::OllamaModelListView(QWidget *parent)
    : QListView(parent)
{
    // setItemDelegate(new OllamaModelInfosDelegate(this));
    // TODO add model too.
}

OllamaModelListView::~OllamaModelListView() = default;

#include "moc_ollamamodellistview.cpp"
