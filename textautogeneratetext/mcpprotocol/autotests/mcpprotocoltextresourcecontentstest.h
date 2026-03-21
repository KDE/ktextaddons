/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolTextResourceContentsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolTextResourceContentsTest(QObject *parent = nullptr);
    ~McpProtocolTextResourceContentsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
