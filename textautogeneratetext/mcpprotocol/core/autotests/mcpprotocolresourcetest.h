/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolResourceTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolResourceTest(QObject *parent = nullptr);
    ~McpProtocolResourceTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
