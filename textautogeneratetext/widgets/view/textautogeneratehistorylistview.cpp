/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistview.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratehistorysortfilterproxymodel.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratehistorylistviewdelegate.h"
#include <KLocalizedString>
#include <QContextMenuEvent>
#include <QMenu>

using namespace TextAutogenerateText;
TextAutogenerateHistoryListView::TextAutogenerateHistoryListView(QWidget *parent)
    : QListView(parent)
    , mHistoryProxyModel(new TextAutoGenerateHistorySortFilterProxyModel(this))
{
    setDragEnabled(false);
    setUniformItemSizes(true);
    // Add delegate
    setItemDelegate(new TextAutogenerateHistoryListViewDelegate(this));

    mHistoryProxyModel->setSourceModel(TextAutogenerateManager::self()->textAutoGenerateChatModel());
    setModel(mHistoryProxyModel);
}

TextAutogenerateHistoryListView::~TextAutogenerateHistoryListView() = default;

void TextAutogenerateHistoryListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto removeHistory = new QAction(i18nc("@action", "Remove…"), &menu);
        connect(removeHistory, &QAction::triggered, this, [index]() {
            const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
            if (!uuid.isEmpty()) {
                TextAutogenerateManager::self()->textAutoGenerateChatModel()->removeDiscussion(uuid);
            }
        });
        menu.addAction(removeHistory);
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

void TextAutogenerateHistoryListView::slotSearchTextChanged(const QString &str)
{
    // Improve it ???
    mHistoryProxyModel->setFilterFixedString(str);
}
#include "moc_textautogeneratehistorylistview.cpp"
