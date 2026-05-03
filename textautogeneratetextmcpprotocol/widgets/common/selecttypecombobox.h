/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "mcpprotocolwidgets_private_export.h"
#include <QComboBox>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT SelectTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SelectTypeComboBox(QWidget *parent = nullptr);
    ~SelectTypeComboBox() override;

    void setType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType type);
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType type() const;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void fill();
};
}
