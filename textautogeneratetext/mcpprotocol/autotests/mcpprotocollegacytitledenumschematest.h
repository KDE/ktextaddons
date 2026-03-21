/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolLegacyTitledEnumSchemaTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolLegacyTitledEnumSchemaTest(QObject *parent = nullptr);
    ~McpProtocolLegacyTitledEnumSchemaTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
