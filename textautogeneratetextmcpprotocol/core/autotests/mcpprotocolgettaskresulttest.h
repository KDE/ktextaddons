/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolGetTaskResultTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolGetTaskResultTest(QObject *parent = nullptr);
    ~McpProtocolGetTaskResultTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertJson();
};
