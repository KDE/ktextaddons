/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpClientUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpClientUtilsTest(QObject *parent = nullptr);
    ~McpClientUtilsTest() override = default;

private Q_SLOTS:
    void shouldParseBearerChallenge_data();
    void shouldParseBearerChallenge();
};
