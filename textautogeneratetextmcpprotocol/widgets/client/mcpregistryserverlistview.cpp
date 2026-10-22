/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpregistryserverlistview.h"
#include "client/mcpregistryserverlistviewdelegate.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerModel>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpRegistryServerListView::McpRegistryServerListView(QWidget *parent)
    : QListView(parent)
    , mModel(new TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel(this))
{
    setItemDelegate(new McpRegistryServerListViewDelegate(this));
    setDragEnabled(false);
    setUniformItemSizes(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setModel(mModel);
    connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &McpRegistryServerListView::slotCurrentChanged);
    connect(mModel, &QAbstractItemModel::modelReset, this, [this]() {
        Q_EMIT serverSelected({});
    });
}

McpRegistryServerListView::~McpRegistryServerListView() = default;

TextAutoGenerateTextMcpProtocolCore::McpRegistryServerModel *McpRegistryServerListView::registryServerModel() const
{
    return mModel;
}

void McpRegistryServerListView::slotCurrentChanged(const QModelIndex &index)
{
    Q_EMIT serverSelected(mModel->serverInfo(index.row()));
}

#include "moc_mcpregistryserverlistview.cpp"
