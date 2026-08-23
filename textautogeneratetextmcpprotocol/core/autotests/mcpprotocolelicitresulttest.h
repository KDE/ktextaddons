/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolElicitResultTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolElicitResultTest(QObject *parent = nullptr);
    ~McpProtocolElicitResultTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertActionToString();
    void shouldConvertJson();
};
