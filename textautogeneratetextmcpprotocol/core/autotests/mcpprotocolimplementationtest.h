/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolImplementationTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolImplementationTest(QObject *parent = nullptr);
    ~McpProtocolImplementationTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
