/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolBooleanSchemaTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolBooleanSchemaTest(QObject *parent = nullptr);
    ~McpProtocolBooleanSchemaTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
