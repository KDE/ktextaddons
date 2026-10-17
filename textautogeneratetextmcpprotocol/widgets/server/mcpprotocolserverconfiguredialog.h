/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolwidgets_private_export.h"
#include <QDialog>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpProtocolServerConfigureWidget;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT McpProtocolServerConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit McpProtocolServerConfigureDialog(QWidget *parent = nullptr);
    ~McpProtocolServerConfigureDialog() override;

private:
    McpProtocolServerConfigureWidget *const mMcpProtocolServerConfigureWidget;
};
}
