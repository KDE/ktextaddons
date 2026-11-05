/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QMap>
#include <QWidget>
class QTableWidget;
class QPushButton;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
/*!
 * \brief Editor for environment variables (name/value) passed to a stdio server
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpStdioServerEnvironmentWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief AddMcpStdioServerEnvironmentWidget
     * \param parent
     */
    explicit AddMcpStdioServerEnvironmentWidget(QWidget *parent = nullptr);
    /*!
     */
    ~AddMcpStdioServerEnvironmentWidget() override;

    /*!
     * \brief environments
     * \return environment variables, rows with empty name are ignored
     */
    [[nodiscard]] QMap<QString, QString> environments() const;
    /*!
     * \brief setEnvironments
     * \param environments
     */
    void setEnvironments(const QMap<QString, QString> &environments);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotAddEnvironment();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotRemoveEnvironment();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void updateButtons();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void addRow(const QString &name, const QString &value);
    QTableWidget *const mTableWidget;
    QPushButton *const mRemoveButton;
};
}
