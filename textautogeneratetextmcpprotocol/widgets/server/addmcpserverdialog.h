/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "addmcpserverwidget.h"
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QDialog>

namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServer;
}

namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpServerDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief AddMcpServerDialog
     * \param parent
     */
    explicit AddMcpServerDialog(QWidget *parent = nullptr);
    /*!
     */
    ~AddMcpServerDialog() override;

    /*!
     * \brief setServerInfo
     * \param server
     */
    void setServerInfo(const TextAutoGenerateTextMcpProtocolCore::McpServer &server);

    /*!
     * \brief serverInfo
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpServer serverInfo() const;

private:
    AddMcpServerWidget *const mAddMcpServerWidget;
};
}
