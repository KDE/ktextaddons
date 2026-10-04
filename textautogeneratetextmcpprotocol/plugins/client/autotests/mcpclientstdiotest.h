/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpClientStdioTest : public QObject
{
    Q_OBJECT
public:
    explicit McpClientStdioTest(QObject *parent = nullptr);
    ~McpClientStdioTest() override = default;

private Q_SLOTS:
    void shouldSendAndReceiveMessages();
    void shouldFinishWhenProcessFailedToStart();
    void shouldSupportQuotedArguments();
    void shouldRejectInvalidArguments();
};
