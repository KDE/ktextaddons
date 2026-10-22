/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QDialog>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpRegistryServerInfo;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpRegistryServerWidget;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpRegistryServerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddMcpRegistryServerDialog(QWidget *parent = nullptr);
    ~AddMcpRegistryServerDialog() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo serverInfo() const;

private:
    AddMcpRegistryServerWidget *const mAddMcpRegistryServerWidget;
};
}
