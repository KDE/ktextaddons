/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpServerTest : public QObject
{
    Q_OBJECT
public:
    explicit McpServerTest(QObject *parent = nullptr);
    ~McpServerTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldVerifyValidValue();
};
