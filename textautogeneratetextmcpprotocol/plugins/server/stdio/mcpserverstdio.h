/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpbase.h"
#include <QByteArray>
class QProcess;
class McpServerStdioPluginInterface;
class McpServerStdio : public TextAutoGenerateTextMcpProtocolCore::McpBase
{
    Q_OBJECT
public:
    explicit McpServerStdio(McpServerStdioPluginInterface *interface, QObject *parent = nullptr);
    ~McpServerStdio() override;

    void connection() override;
    void send(const QJsonObject &obj) override;

    void stop();

    [[nodiscard]] bool isRunning() const;

private:
    void slotReadStandardOutput();
    void slotReadStandardError();
    QProcess *const mProcess;
    McpServerStdioPluginInterface *const mInterface;
    QByteArray mBuffer;
};
