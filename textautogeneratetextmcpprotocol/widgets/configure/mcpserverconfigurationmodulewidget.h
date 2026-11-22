/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
class QCheckBox;
class QDebug;
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

    /*!
     * \brief Returns the name of the configuration file used to load and save the settings.
     */
    [[nodiscard]] QString configName() const;
    /*!
     * \brief Sets the name of the configuration file used to load and save the settings.
     * \param newConfigName the configuration file name (e.g. "kdeworkspacemcprc")
     */
    void setConfigName(const QString &newConfigName);

    /*!
     * \brief dbusName
     * \return
     */
    [[nodiscard]] QString dbusName() const;
    /*!
     * \brief setDbusName
     * \param newDbusName
     */
    void setDbusName(const QString &newDbusName);

    /*!
     * \brief execName
     * \return
     */
    [[nodiscard]] QString execName() const;
    /*!
     * \brief setExecName
     * \param newExecName
     */
    void setExecName(const QString &newExecName);

Q_SIGNALS:
    /*!
     * \brief configureChanged
     */
    void configureChanged();

    /*!
     * \brief Emitted when the settings have been loaded, to reset the "needs save" state.
     * \param state true if the module has unsaved changes, false otherwise
     */
    void needSave(bool state);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void reloadServer();
    QString mConfigName;
    QString mDbusName;
    QString mExecName;
    TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget *const mMcpProtocolServerConfigureWidget;
    QCheckBox *const mEnabled;
    QCheckBox *const mConfirmModify;
};
}
TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolWidgets::MCPServerConfigurationModuleWidget &t);
