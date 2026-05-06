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
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpStdioServerWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief AddMcpStdioServerWidget
     * \param parent
     */
    explicit AddMcpStdioServerWidget(QWidget *parent = nullptr);
    /*!
     */
    ~AddMcpStdioServerWidget() override;
Q_SIGNALS:
    void settingChanged();

private:
    QLineEdit *const mCommandLineEdit;
    QLineEdit *const mArgumentsLineEdit;
};
}
