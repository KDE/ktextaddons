/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "addmcpserverwidget.h"
#include <QDialog>

namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpServerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddMcpServerDialog(QWidget *parent = nullptr);
    ~AddMcpServerDialog() override;

    void setServerWidgetInfo(const AddMcpServerWidget::McpServerWidgetInfo &info);
    [[nodiscard]] AddMcpServerWidget::McpServerWidgetInfo serverWidgetInfo() const;

private:
    AddMcpServerWidget *const mAddMcpServerWidget;
};
}
