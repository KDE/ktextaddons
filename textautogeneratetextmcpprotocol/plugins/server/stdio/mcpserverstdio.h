/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpbase.h"
#include <QByteArray>
#include <QFile>
class QSocketNotifier;
/*
 * Server side of the stdio transport: client launches server process,
 * messages are read in stdin and written in stdout (newline delimited json).
 * Nothing else must be written in stdout, logs go to stderr.
 */
class McpServerStdio : public TextAutoGenerateTextMcpProtocolCore::McpBase
{
    Q_OBJECT
public:
    explicit McpServerStdio(QObject *parent = nullptr);
    ~McpServerStdio() override;

    void connection() override;
    void send(const QJsonObject &obj) override;
    void stop() override;

    [[nodiscard]] bool isRunning() const;

private:
    void slotReadStandardInput();
    void processBuffer();
    QSocketNotifier *mNotifier = nullptr;
    QFile mStandardOutput;
    QByteArray mBuffer;
    bool mStarted = false;
};
