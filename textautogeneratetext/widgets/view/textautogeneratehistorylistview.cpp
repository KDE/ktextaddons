/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistview.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratehistorymodel.h"
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
    setUniformItemSizes(false);
    setItemDelegate(new TextAutogenerateHistoryListViewDelegate(this));

    auto historyModel = new TextAutoGenerateHistoryModel(this);
    historyModel->setSourceModel(TextAutogenerateManager::self()->textAutoGenerateChatModel());
    mHistoryProxyModel->setSourceModel(historyModel);
    setModel(mHistoryProxyModel);

    connect(this, &TextAutogenerateHistoryListView::clicked, this, &TextAutogenerateHistoryListView::slotClicked);
}

TextAutogenerateHistoryListView::~TextAutogenerateHistoryListView() = default;

void TextAutogenerateHistoryListView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        event->accept();
    } else {
        QListView::keyPressEvent(event);
    }
}
void TextAutogenerateHistoryListView::slotClicked(const QModelIndex &idx)
{
    if (idx.isValid()) {
        const QByteArray uuid = idx.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
        if (!uuid.isEmpty()) {
            Q_EMIT goToDiscussion(uuid);
        }
    }
}

void TextAutogenerateHistoryListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto renameHistory = new QAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18nc("@action", "Modify…"), &menu);
        connect(renameHistory, &QAction::triggered, this, [index, this]() {
            const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
            if (!uuid.isEmpty()) {
                edit(index);
            }
        });
        menu.addAction(renameHistory);

        menu.addSeparator();

        auto removeHistory = new QAction(QIcon::fromTheme(QStringLiteral("list-remove")), i18nc("@action", "Remove…"), &menu);
        connect(removeHistory, &QAction::triggered, this, [index]() {
            const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
            if (!uuid.isEmpty()) {
                TextAutogenerateManager::self()->textAutoGenerateChatModel()->removeDiscussion(uuid);
            }
        });
        menu.addAction(removeHistory);

        const bool archived = index.data(TextAutoGenerateChatModel::ArchivedRole).toBool();
        menu.addSeparator();
        if (archived) {
            auto restoreArchivedAction = new QAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18nc("@action", "Restore"), &menu);
            connect(restoreArchivedAction, &QAction::triggered, this, [index]() {
                /*
                const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
                if (!uuid.isEmpty()) {
                    TextAutogenerateManager::self()->textAutoGenerateChatModel()->removeDiscussion(uuid);
                }
                */
            });
            menu.addAction(restoreArchivedAction);
        } else {
#if 0
            auto archiveAction = new QAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18nc("@action", "Restore"), &menu);
            connect(archiveAction, &QAction::triggered, this, [index]() {
                /*
                const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
                if (!uuid.isEmpty()) {
                    TextAutogenerateManager::self()->textAutoGenerateChatModel()->removeDiscussion(uuid);
                }
                */
            });
            menu.addAction(archiveAction);
#endif
            // TODO
        }
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

void TextAutogenerateHistoryListView::slotSearchTextChanged(const QString &str)
{
    mHistoryProxyModel->setFilterFixedString(str);
}
#include "moc_textautogeneratehistorylistview.cpp"
