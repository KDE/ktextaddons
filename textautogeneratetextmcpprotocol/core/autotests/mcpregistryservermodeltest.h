/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class McpRegistryServerModelTest : public QObject
{
    Q_OBJECT
public:
    explicit McpRegistryServerModelTest(QObject *parent = nullptr);
    ~McpRegistryServerModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAppendServers();
};
