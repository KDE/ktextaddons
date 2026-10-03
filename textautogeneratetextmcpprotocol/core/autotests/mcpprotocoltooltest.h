/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolToolTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolToolTest(QObject *parent = nullptr);
    ~McpProtocolToolTest() override = default;

private Q_SLOTS:
    void shouldKeepAllInputSchemaKeywords();
    void shouldKeepAllOutputSchemaKeywords();
};
