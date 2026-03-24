/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolCompleteRequestParamsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolCompleteRequestParamsTest(QObject *parent = nullptr);
    ~McpProtocolCompleteRequestParamsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
