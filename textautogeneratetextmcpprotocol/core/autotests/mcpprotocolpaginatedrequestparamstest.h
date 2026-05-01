/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolPaginatedRequestParamsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolPaginatedRequestParamsTest(QObject *parent = nullptr);
    ~McpProtocolPaginatedRequestParamsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
