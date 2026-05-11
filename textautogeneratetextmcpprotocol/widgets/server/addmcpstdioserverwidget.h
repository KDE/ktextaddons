/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "addmcpserverbasewidget.h"
#include "textautogeneratetextmcpprotocolwidgets_export.h"
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpStdioServerWidget : public AddMcpServerBaseWidget
{
    Q_OBJECT
public:
    struct StdioInfo {
        QString command;
        QString arguments;
    };

    /*!
     * \brief AddMcpStdioServerWidget
     * \param parent
     */
    explicit AddMcpStdioServerWidget(QWidget *parent = nullptr);
    /*!
     */
    ~AddMcpStdioServerWidget() override;

    /*!
     * \brief setStdioInfo
     * \param info
     */
    void setStdioInfo(const StdioInfo &info);
    /*!
     * \brief stdioInfo
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerWidget::StdioInfo stdioInfo() const;

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
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerWidget::StdioInfo, Q_RELOCATABLE_TYPE);
