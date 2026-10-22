/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
class KEditListWidget;
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
/*!
 * Edit local directories that server is allowed to access (MCP "roots").
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpServerRootsWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief AddMcpServerRootsWidget
     * \param parent
     */
    explicit AddMcpServerRootsWidget(QWidget *parent = nullptr);
    /*!
     * \brief ~AddMcpServerRootsWidget
     */
    ~AddMcpServerRootsWidget() override;

    /*!
     * \brief roots
     * \return
     */
    [[nodiscard]] QStringList roots() const;
    /*!
     * \brief setRoots
     * \param roots
     */
    void setRoots(const QStringList &roots);

Q_SIGNALS:
    /*!
     * \brief rootsChanged
     */
    void rootsChanged();

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void selectDirectory();
    QLineEdit *const mDirectoryLineEdit;
    KEditListWidget *const mEditListWidget;
};
}
