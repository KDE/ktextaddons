/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverlistview.h"
#include "models/mcpservermodel.h"
#include "models/mcpserversortfilterproxymodel.h"
#include "server/mcpservermanager.h"
#include "textautogeneratetextmcpprotocol_widgets_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
McpServerListView::McpServerListView(QWidget *parent)
    : QListView(parent)
    , mSortFilterProxyModel(new TextAutoGenerateTextMcpProtocolCore::McpServerSortFilterProxyModel(this))
{
    setDragEnabled(false);
#if 0
    if (manager) {
        mSortFilterProxyModel->setSourceModel(manager->textAutoGenerateTextMcpServerManager()->textAutoGenerateTextMcpServerModel());
    }
#endif
    setModel(mSortFilterProxyModel);
    connect(this, &QListView::doubleClicked, this, &McpServerListView::slotEditMcpServer);
}

McpServerListView::~McpServerListView() = default;

void McpServerListView::slotSearchChanged(const QString &str)
{
    mSortFilterProxyModel->setSearchText(str);
}

void McpServerListView::slotEditMcpServer(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateTextMcpProtocolCore::McpServerModel::Identifier).toByteArray();
    if (uuid.isEmpty()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "invalid mcp instance uuid";
    } else {
        Q_EMIT editServer(uuid);
    }
}

void McpServerListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addServerAction = new QAction(i18nc("@action", "Add server…"), &menu);
    menu.addAction(addServerAction);
    connect(addServerAction, &QAction::triggered, this, &McpServerListView::addServer);

    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        menu.addSeparator();
        auto editAction = new QAction(QIcon::fromTheme(u"edit-rename"_s), i18nc("@action", "Edit…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            slotEditMcpServer(index);
        });
        menu.addAction(editAction);
        menu.addSeparator();
        auto removeAction = new QAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove Server"), &menu);
        connect(removeAction, &QAction::triggered, this, [index, this]() {
            const QByteArray uuid = index.data(TextAutoGenerateTextMcpProtocolCore::McpServerModel::Identifier).toByteArray();
            if (uuid.isEmpty()) {
                qCWarning(TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG) << "invalid identifier";
            } else {
                const QString name = index.data(TextAutoGenerateTextMcpProtocolCore::McpServerModel::Name).toString();
                if (KMessageBox::warningTwoActions(this,
                                                   i18n("Do you want to remove this server (%1)?", name),
                                                   i18nc("@title", "Remove Server"),
                                                   KStandardGuiItem::remove(),
                                                   KStandardGuiItem::cancel())
                    == KMessageBox::PrimaryAction) {
                    Q_EMIT removeServer(uuid);
                }
            }
        });
        menu.addAction(removeAction);
    }
    menu.exec(event->globalPos());
}

#include "moc_mcpserverlistview.cpp"
