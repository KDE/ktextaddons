/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpClientStreamableHttpTest : public QObject
{
    Q_OBJECT
public:
    explicit McpClientStreamableHttpTest(QObject *parent = nullptr);
    ~McpClientStreamableHttpTest() override = default;

private Q_SLOTS:
    void shouldNotStartWithInvalidUrl();
    void shouldUseSessionAndProtocolVersion();
    void shouldResumeInterruptedStream();
    void shouldCreateErrorResponseWhenStreamCantBeResumed();
    void shouldCreateErrorResponseWhenPostFailed();
    void shouldFinishWhenSessionExpired();
    void shouldDeleteSessionWhenStopped();
    void shouldDeleteSessionWhenClientIsDeletedAfterStop();
    void shouldReconnectEventStream();
};
