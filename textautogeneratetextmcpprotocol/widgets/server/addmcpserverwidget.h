/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
class QLineEdit;
class QStackedWidget;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServer;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class SelectTypeComboBox;
class AddMcpSseServerWidget;
class AddMcpStdioServerWidget;
class AddMcpSteamableHttpServerWidget;

class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpServerWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief AddMcpServerWidget
     * \param parent
     */
    explicit AddMcpServerWidget(QWidget *parent = nullptr);
    /*!
     */
    ~AddMcpServerWidget() override;

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

Q_SIGNALS:
    /*!
     * \brief buttonOkEnabled
     * \param state
     */
    void buttonOkEnabled(bool state);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void checkValidSettings();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void changeType();
    QLineEdit *const mServerNameLineEdit;
    SelectTypeComboBox *const mSelectTypeComboBox;
    QStackedWidget *const mStackedWidget;
    AddMcpSseServerWidget *const mAddMcpSseServerWidget;
    AddMcpStdioServerWidget *const mAddMcpStdioServerWidget;
    AddMcpSteamableHttpServerWidget *const mAddMcpSteamableHttpServerWidget;
};
}
