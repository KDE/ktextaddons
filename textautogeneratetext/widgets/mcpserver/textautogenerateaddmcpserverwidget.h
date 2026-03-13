/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateAddMcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    struct McpServerWidgetInfo {
        QString name;
        QString serverUrl;
    };
    explicit TextAutoGenerateAddMcpServerWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateAddMcpServerWidget() override;

    void setServerWidgetInfo(const McpServerWidgetInfo &info);
    [[nodiscard]] McpServerWidgetInfo serverWidgetInfo() const;
Q_SIGNALS:
    void buttonOkEnabled(bool state);

private:
    QLineEdit *const mServerNameLineEdit;
    QLineEdit *const mServerUrlLineEdit;
};
}
