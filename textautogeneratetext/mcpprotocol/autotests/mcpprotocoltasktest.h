/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolTaskTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolTaskTest(QObject *parent = nullptr);
    ~McpProtocolTaskTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
