/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolwidgets_private_export.h"
#include <QWidget>
class KEditListWidget;
class QLineEdit;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
/*!
 * Edit local directories that server is allowed to access (MCP "roots").
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpServerRootsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpServerRootsWidget(QWidget *parent = nullptr);
    ~AddMcpServerRootsWidget() override;

    [[nodiscard]] QStringList roots() const;
    void setRoots(const QStringList &roots);

Q_SIGNALS:
    void rootsChanged();

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void selectDirectory();
    QLineEdit *const mDirectoryLineEdit;
    KEditListWidget *const mEditListWidget;
};
}
