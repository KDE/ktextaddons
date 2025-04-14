/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistview.h"
#include "textautogeneratehistorylistviewdelegate.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>

using namespace TextAutogenerateText;
TextAutogenerateHistoryListView::TextAutogenerateHistoryListView(QWidget *parent)
    : QListView(parent)
{
    setDragEnabled(false);
    setUniformItemSizes(true);
    // Add delegate
    setItemDelegate(new TextAutogenerateHistoryListViewDelegate(this));
}

TextAutogenerateHistoryListView::~TextAutogenerateHistoryListView() = default;

void TextAutogenerateHistoryListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto removeHistory = new QAction(i18nc("@action", "Remove…"), &menu);
        connect(removeHistory, &QAction::triggered, this, [this]() {
            // TODO
        });
        menu.addAction(removeHistory);
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

#include "moc_textautogeneratehistorylistview.cpp"
