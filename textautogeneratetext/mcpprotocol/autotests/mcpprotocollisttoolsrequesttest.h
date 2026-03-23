/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolListToolsRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolListToolsRequestTest(QObject *parent = nullptr);
    ~McpProtocolListToolsRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
