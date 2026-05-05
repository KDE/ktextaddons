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
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpSseServerWidget : public QWidget
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

private:
    QLineEdit *const mServerUrlLineEdit;
};
}
