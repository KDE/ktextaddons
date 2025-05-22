/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfosdelegate.h"

OllamaModelInfosDelegate::OllamaModelInfosDelegate(QListView *view)
    : TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate(view)
{
}

OllamaModelInfosDelegate::~OllamaModelInfosDelegate() = default;

QTextDocument *OllamaModelInfosDelegate::documentForIndex(const QModelIndex &index, int width) const
{
    // TODO
    return nullptr;
}

#include "moc_ollamamodelinfosdelegate.cpp"
