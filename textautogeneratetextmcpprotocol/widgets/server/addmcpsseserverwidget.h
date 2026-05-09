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
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpSseServerWidget : public AddMcpServerBaseWidget
{
    Q_OBJECT
public:
    /*!
     * \brief AddMcpSseServerWidget
     * \param parent
     */
    explicit AddMcpSseServerWidget(QWidget *parent = nullptr);
    /*!
     */
    ~AddMcpSseServerWidget() override;

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
