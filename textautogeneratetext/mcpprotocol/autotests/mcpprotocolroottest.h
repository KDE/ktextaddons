/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolRootTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolRootTest(QObject *parent = nullptr);
    ~McpProtocolRootTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
