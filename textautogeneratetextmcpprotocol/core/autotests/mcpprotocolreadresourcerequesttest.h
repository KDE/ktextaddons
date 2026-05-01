/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolReadResourceRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolReadResourceRequestTest(QObject *parent = nullptr);
    ~McpProtocolReadResourceRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
