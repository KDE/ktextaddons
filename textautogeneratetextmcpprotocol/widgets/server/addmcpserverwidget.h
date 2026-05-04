/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class SelectTypeComboBox;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    struct McpServerWidgetInfo {
        QString name;
        QString serverUrl;
    };
    explicit AddMcpServerWidget(QWidget *parent = nullptr);
    ~AddMcpServerWidget() override;

    void setServerWidgetInfo(const McpServerWidgetInfo &info);
    [[nodiscard]] McpServerWidgetInfo serverWidgetInfo() const;
Q_SIGNALS:
    void buttonOkEnabled(bool state);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void checkValidSettings();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void changeType(int index);
    QLineEdit *const mServerNameLineEdit;
    QLineEdit *const mServerUrlLineEdit;
    SelectTypeComboBox *const mSelectTypeComboBox;
};
}
