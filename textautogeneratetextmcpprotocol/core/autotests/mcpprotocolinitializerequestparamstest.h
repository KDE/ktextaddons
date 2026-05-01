/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolInitializeRequestParamsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolInitializeRequestParamsTest(QObject *parent = nullptr);
    ~McpProtocolInitializeRequestParamsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
