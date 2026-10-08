/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpServerStreamableHttpTest : public QObject
{
    Q_OBJECT
public:
    explicit McpServerStreamableHttpTest(QObject *parent = nullptr);
    ~McpServerStreamableHttpTest() override = default;

private Q_SLOTS:
    void shouldNotStartWithInvalidUrl();
    void shouldExchangeMessagesWithClient();
    void shouldRejectRequestWithoutSession();
    void shouldRejectRequestWithUnknownSession();
    void shouldRejectInvalidRequests();
    void shouldAnswerBatch();
    void shouldTerminateSession();
};
