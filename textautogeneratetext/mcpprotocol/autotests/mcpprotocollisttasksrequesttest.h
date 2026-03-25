/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolListTasksRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolListTasksRequestTest(QObject *parent = nullptr);
    ~McpProtocolListTasksRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
