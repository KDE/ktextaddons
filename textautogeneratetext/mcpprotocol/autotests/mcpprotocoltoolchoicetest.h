/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolToolChoiceTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolToolChoiceTest(QObject *parent = nullptr);
    ~McpProtocolToolChoiceTest() override = default;

private Q_SLOTS:
    void shouldhaveDefaultValues();
};
