/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpServerStdioTest : public QObject
{
    Q_OBJECT
public:
    explicit McpServerStdioTest(QObject *parent = nullptr);
    ~McpServerStdioTest() override = default;

private Q_SLOTS:
    void shouldExchangeMessagesWithClient();
    void shouldExitWhenStdinIsClosed();
    void shouldIgnoreInvalidJson();
    void shouldReadMessageSplitInSeveralWrites();
};
