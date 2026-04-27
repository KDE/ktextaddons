/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolCancelTaskRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolCancelTaskRequestTest(QObject *parent = nullptr);
    ~McpProtocolCancelTaskRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
