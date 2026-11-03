/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolServerToolArgumentsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServerToolArgumentsTest(QObject *parent = nullptr);
    ~McpProtocolServerToolArgumentsTest() override = default;

private Q_SLOTS:
    void shouldCheckIsProvided();
    void shouldReadInteger();
    void shouldReadNumber();
    void shouldReadBoolean();
    void shouldReadStringList();
    void shouldReadOptionalString();
};
