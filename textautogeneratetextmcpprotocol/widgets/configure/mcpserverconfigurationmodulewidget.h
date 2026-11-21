/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
class QCheckBox;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpProtocolServerConfigureWidget;
/*!
 * \class TextAutoGenerateTextMcpProtocolWidgets::MCPServerConfigurationModuleWidget
 * \brief The MCPServerConfigurationModuleWidget class.
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateTextMcpProtocolWidgets
 * \inheaderfile TextAutoGenerateTextMcpProtocolWidgets/MCPServerConfigurationModuleWidget
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT MCPServerConfigurationModuleWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief MCPServerConfigurationModuleWidget
     * \param parent
     */
    explicit MCPServerConfigurationModuleWidget(QWidget *parent = nullptr);
    /*!
     * \brief ~MCPServerConfigurationModuleWidget
     */
    ~MCPServerConfigurationModuleWidget() override;

    /*!
     * \brief load
     */
    void load();
    /*!
     * \brief save
     */
    void save();
    /*!
     * \brief defaults
     */
    void defaults();

Q_SIGNALS:
    /*!
     * \brief configureChanged
     */
    void configureChanged();

private:
    void reloadServer();
    TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget *const mMcpProtocolServerConfigureWidget;
    QCheckBox *const mEnabled;
    QCheckBox *const mConfirmModify;
};
}
