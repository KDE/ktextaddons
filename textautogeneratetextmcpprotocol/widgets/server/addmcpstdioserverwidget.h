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
    [[nodiscard]] bool isValid() const;

Q_SIGNALS:
    void settingChanged();

private:
    QLineEdit *const mCommandLineEdit;
    QLineEdit *const mArgumentsLineEdit;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerWidget::StdioInfo, Q_RELOCATABLE_TYPE);
