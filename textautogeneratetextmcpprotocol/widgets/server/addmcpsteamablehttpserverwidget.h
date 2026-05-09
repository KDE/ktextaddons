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
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpSteamableHttpServerWidget : public AddMcpServerBaseWidget
{
    Q_OBJECT
public:
    /*!
     * \brief AddMcpSteamableHttpServerWidget
     * \param parent
     */
    explicit AddMcpSteamableHttpServerWidget(QWidget *parent = nullptr);
    /*!
     */
    ~AddMcpSteamableHttpServerWidget() override;

    /*!
     * \brief setUrl
     * \param str
     */
    void setUrl(const QString &str);
    /*!
     * \brief url
     * \return
     */
    [[nodiscard]] QString url() const;

    /*!
     * \brief isValid
     * \return
     */
    [[nodiscard]] bool isValid() const;

private:
    QLineEdit *const mServerUrlLineEdit;
};
}
