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
class McpServerModel;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT McpServerListView : public QListView
{
    Q_OBJECT
public:
    /*!
     * \brief McpServerListView
     * \param model
     * \param parent
     */
    explicit McpServerListView(TextAutoGenerateTextMcpProtocolCore::McpServerModel *model, QWidget *parent = nullptr);
    /*!
     */
    ~McpServerListView() override;

    /*!
     * \brief slotSearchChanged
     * \param str
     */
    void slotSearchChanged(const QString &str);

Q_SIGNALS:
    /*!
     * \brief addServer
     */
    void addServer();
    /*!
     * \brief editServer
     * \param id
     */
    void editServer(const QByteArray &id);
    /*!
     * \brief removeServer
     * \param id
     */
    void removeServer(const QByteArray &id);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotEditMcpServer(const QModelIndex &index);
    TextAutoGenerateTextMcpProtocolCore::McpServerSortFilterProxyModel *const mSortFilterProxyModel;
};
}
