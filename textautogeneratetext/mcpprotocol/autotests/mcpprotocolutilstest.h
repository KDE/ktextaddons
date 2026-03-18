/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolUtilsTest(QObject *parent = nullptr);
    ~McpProtocolUtilsTest() override = default;

private Q_SLOTS:
    void shouldConvertRoleToString();
    void shouldConvertRoleFromString();
    void shouldConvertLoggingLevelToString();
    void shouldConvertLoggingLevelFromString();
    void shouldConvertTaskStatusToString();
    void shouldConvertTaskStatusFromString();
};
