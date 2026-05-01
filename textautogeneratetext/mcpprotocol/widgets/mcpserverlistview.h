/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QListView>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServerSortFilterProxyModel;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT McpServerListView : public QListView
{
    Q_OBJECT
public:
    explicit McpServerListView(QWidget *parent = nullptr);
    ~McpServerListView() override;

    void slotSearchChanged(const QString &str);

Q_SIGNALS:
    void addServer();
    void editServer(const QByteArray &id);
    void removeServer(const QByteArray &id);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotEditMcpServer(const QModelIndex &index);
    TextAutoGenerateTextMcpProtocolCore::McpServerSortFilterProxyModel *const mSortFilterProxyModel;
};
}
