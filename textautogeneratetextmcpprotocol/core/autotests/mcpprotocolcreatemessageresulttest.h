/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolCreateMessageResultTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolCreateMessageResultTest(QObject *parent = nullptr);
    ~McpProtocolCreateMessageResultTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertJson();
};
