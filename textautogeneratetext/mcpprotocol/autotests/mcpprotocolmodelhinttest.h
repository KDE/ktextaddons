/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolModelHintTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolModelHintTest(QObject *parent = nullptr);
    ~McpProtocolModelHintTest() override = default;

private Q_SLOTS:
    void shouldhaveDefaultValues();
};
