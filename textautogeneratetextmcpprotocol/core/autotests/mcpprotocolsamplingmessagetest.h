/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolSamplingMessageTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolSamplingMessageTest(QObject *parent = nullptr);
    ~McpProtocolSamplingMessageTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertJson();
};
