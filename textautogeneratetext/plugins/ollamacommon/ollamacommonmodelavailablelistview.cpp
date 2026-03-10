/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelavailablelistview.h"
#include "ollamacommonmodelavailableinfosdelegate.h"

OllamaCommonModelAvailableListView::OllamaCommonModelAvailableListView(QWidget *parent)
    : TextAutoGenerateText::TextAutoGenerateModelAvailableListView(parent)
    , mAvailableInfosDelegate(new OllamaCommonModelAvailableInfosDelegate(this))
{
    setItemDelegate(mAvailableInfosDelegate);
}

OllamaCommonModelAvailableListView::~OllamaCommonModelAvailableListView() = default;

void OllamaCommonModelAvailableListView::resizeEvent(QResizeEvent *ev)
{
    TextAutoGenerateText::TextAutoGenerateModelAvailableListView::resizeEvent(ev);
    mAvailableInfosDelegate->clearSizeHintCache();
}

#include "moc_ollamacommonmodelavailablelistview.cpp"
