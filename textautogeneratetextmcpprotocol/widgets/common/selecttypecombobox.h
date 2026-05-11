/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "mcpprotocolwidgets_private_export.h"
#include <QComboBox>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT SelectTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SelectTypeComboBox(QWidget *parent = nullptr);
    ~SelectTypeComboBox() override;

    void setType(TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType type);
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType type() const;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void fill();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void addServerType(TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType type);
};
}
