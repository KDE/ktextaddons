/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistview.h"
#include "core/textautogeneratechatsmodel.h"
#include "core/textautogeneratehistorylistheadingsproxymodel.h"
#include "core/textautogeneratehistorysortfilterproxymodel.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratehistorylistviewdelegate.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>

using namespace TextAutoGenerateText;
TextAutoGenerateHistoryListView::TextAutoGenerateHistoryListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QTreeView(parent)
    , mHistoryProxyModel(new TextAutoGenerateHistorySortFilterProxyModel(this))
    , mHistoryListHeadingsProxyModel(new TextAutoGenerateHistoryListHeadingsProxyModel(this))
    , mManager(manager)
{
    setHeaderHidden(true);
    setDragEnabled(false);
    setIndentation(0);
    setRootIsDecorated(false);
    setItemsExpandable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setItemDelegate(new TextAutoGenerateHistoryListViewDelegate(this));

    if (mManager) {
        mHistoryListHeadingsProxyModel->setSourceModel(mManager->textAutoGenerateChatsModel());
    }

    mHistoryProxyModel->setSourceModel(mHistoryListHeadingsProxyModel);
    setModel(mHistoryProxyModel);
    connect(model(), &QAbstractItemModel::rowsInserted, this, &QTreeView::expandAll);
    connect(model(), &QAbstractItemModel::modelReset, this, &QTreeView::expandAll);
    connect(model(), &QAbstractItemModel::rowsMoved, this, &QTreeView::expandAll);
    connect(model(), &QAbstractItemModel::layoutChanged, this, &QTreeView::expandAll);
    connect(this, &TextAutoGenerateHistoryListView::clicked, this, &TextAutoGenerateHistoryListView::slotClicked);
    expandAll();
}

TextAutoGenerateHistoryListView::~TextAutoGenerateHistoryListView() = default;

void TextAutoGenerateHistoryListView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        event->accept();
    } else {
        QTreeView::keyPressEvent(event);
    }
}
void TextAutoGenerateHistoryListView::slotClicked(const QModelIndex &idx)
{
    if (idx.isValid()) {
        const QByteArray uuid = idx.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
        qDebug() << " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << uuid;
        if (!uuid.isEmpty()) {
            Q_EMIT switchToChat(uuid);
        }
    }
}

void TextAutoGenerateHistoryListView::contextMenuEvent(QContextMenuEvent *event)
{
    const QModelIndex index = indexAt(event->pos());
    if (!index.parent().isValid()) {
        return;
    }

    QMenu menu(this);
    if (index.isValid()) {
        auto renameHistory = new QAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18nc("@action", "Modify…"), &menu);
        connect(renameHistory, &QAction::triggered, this, [index, this]() {
            const QByteArray uuid = index.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
            if (!uuid.isEmpty()) {
                edit(index);
            }
        });
        menu.addAction(renameHistory);

        menu.addSeparator();

        auto removeHistory = new QAction(QIcon::fromTheme(QStringLiteral("list-remove")), i18nc("@action", "Remove…"), &menu);
        connect(removeHistory, &QAction::triggered, this, [index, this]() {
            if (KMessageBox::ButtonCode::PrimaryAction
                == KMessageBox::questionTwoActions(this,
                                                   i18n("Do you want to remove this discussion?"),
                                                   i18nc("@title:window", "Remove Discussion"),
                                                   KStandardGuiItem::remove(),
                                                   KStandardGuiItem::cancel())) {
                const QByteArray uuid = index.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
                if (!uuid.isEmpty()) {
                    // TODO mManager->textAutoGenerateMessagesModel()->removeDiscussion(uuid);
                }
            }
        });
        menu.addAction(removeHistory);

#if 0
        const bool archived = index.data(TextAutoGenerateChatModel::ArchivedRole).toBool();
        menu.addSeparator();
        if (archived) {
            auto restoreArchivedAction = new QAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18nc("@action", "Restore"), &menu);
            connect(restoreArchivedAction, &QAction::triggered, this, [index]() {
                /*
                const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
                if (!uuid.isEmpty()) {
                    mManager->textAutoGenerateChatModel()->removeDiscussion(uuid);
                }
                */
            });
            menu.addAction(restoreArchivedAction);
        } else {
            auto archiveAction = new QAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18nc("@action", "Restore"), &menu);
            connect(archiveAction, &QAction::triggered, this, [index]() {
                /*
                const QByteArray uuid = index.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
                if (!uuid.isEmpty()) {
                    mManager->textAutoGenerateChatModel()->removeDiscussion(uuid);
                }
                */
            });
            menu.addAction(archiveAction);
            // TODO
        }
#endif
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

void TextAutoGenerateHistoryListView::slotSearchTextChanged(const QString &str)
{
    mHistoryProxyModel->setFilterFixedString(str);
}
#include "moc_textautogeneratehistorylistview.cpp"
