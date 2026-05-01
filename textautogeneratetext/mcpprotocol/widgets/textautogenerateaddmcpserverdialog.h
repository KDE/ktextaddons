/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateaddmcpserverwidget.h"
#include <QDialog>

namespace TextAutoGenerateText
{
class TextAutoGenerateAddMcpServerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAddMcpServerDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateAddMcpServerDialog() override;

    void setServerWidgetInfo(const TextAutoGenerateAddMcpServerWidget::McpServerWidgetInfo &info);
    [[nodiscard]] TextAutoGenerateAddMcpServerWidget::McpServerWidgetInfo serverWidgetInfo() const;

private:
    TextAutoGenerateAddMcpServerWidget *const mTextAutoGenerateAddMcpServerWidget;
};
}
