/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolIconTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolIconTest(QObject *parent = nullptr);
    ~McpProtocolIconTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
