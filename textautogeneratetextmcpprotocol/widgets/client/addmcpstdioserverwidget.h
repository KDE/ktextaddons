/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "addmcpserverbasewidget.h"
#include "mcpprotocolwidgets_private_export.h"
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpStdioServerWidget : public AddMcpServerBaseWidget
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

    /*!
     * \brief isValid
     * \return
     */
    [[nodiscard]] bool isValid() const override;

    /*!
     * \brief saveSettings
     * \param server
     */
    void saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server) override;
    /*!
     * \brief loadSettings
     * \param server
     */
    void loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server) override;

private:
    QLineEdit *const mCommandLineEdit;
    QLineEdit *const mArgumentsLineEdit;
};
}
