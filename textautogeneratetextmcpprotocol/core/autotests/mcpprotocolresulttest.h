/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolResultTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolResultTest(QObject *parent = nullptr);
    ~McpProtocolResultTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
