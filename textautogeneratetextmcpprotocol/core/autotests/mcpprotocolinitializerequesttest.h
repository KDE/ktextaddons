/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolInitializeRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolInitializeRequestTest(QObject *parent = nullptr);
    ~McpProtocolInitializeRequestTest() override = default;

private Q_SLOTS:
    void shouldAlwaysSerializeParams();
    void shouldLoadAndSaveRequest();
};
