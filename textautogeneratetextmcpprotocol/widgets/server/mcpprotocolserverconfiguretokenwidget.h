/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolwidgets_private_export.h"
#include <QWidget>

namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT McpProtocolServerConfigureTokenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit McpProtocolServerConfigureTokenWidget(QWidget *parent = nullptr);
    ~McpProtocolServerConfigureTokenWidget() override;
};
}
