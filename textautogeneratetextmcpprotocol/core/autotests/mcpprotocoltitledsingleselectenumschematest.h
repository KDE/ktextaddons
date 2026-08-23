/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolTitledSingleSelectEnumSchemaTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolTitledSingleSelectEnumSchemaTest(QObject *parent = nullptr);
    ~McpProtocolTitledSingleSelectEnumSchemaTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertJson();
};
