/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "addmcpserverwidget.h"
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QDialog>

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
     * \brief setServerWidgetInfo
     * \param info
     */
    void setServerWidgetInfo(const AddMcpServerWidget::McpServerWidgetInfo &info);
    /*!
     * \brief serverWidgetInfo
     * \return
     */
    [[nodiscard]] AddMcpServerWidget::McpServerWidgetInfo serverWidgetInfo() const;

private:
    AddMcpServerWidget *const mAddMcpServerWidget;
};
}
