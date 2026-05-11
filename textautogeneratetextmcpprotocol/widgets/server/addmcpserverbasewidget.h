/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServer;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpServerBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpServerBaseWidget(QWidget *parent = nullptr);
    ~AddMcpServerBaseWidget() override;

    [[nodiscard]] virtual bool isValid() const = 0;

    virtual void saveSettings(TextAutoGenerateTextMcpProtocolCore::McpServer &server) = 0;
    virtual void loadSettings(const TextAutoGenerateTextMcpProtocolCore::McpServer &server) = 0;

Q_SIGNALS:
    void settingChanged();
};
}
