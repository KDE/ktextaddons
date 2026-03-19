/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolStringSchemaTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolStringSchemaTest(QObject *parent = nullptr);
    ~McpProtocolStringSchemaTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
