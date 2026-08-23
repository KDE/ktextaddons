/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolElicitRequestFormParamsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolElicitRequestFormParamsTest(QObject *parent = nullptr);
    ~McpProtocolElicitRequestFormParamsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertJson();
};
