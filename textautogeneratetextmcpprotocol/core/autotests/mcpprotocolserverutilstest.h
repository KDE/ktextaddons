/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolServerUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServerUtilsTest(QObject *parent = nullptr);
    ~McpProtocolServerUtilsTest() override = default;

private Q_SLOTS:
    void initTestCase();
    void shouldHaveDefaultValues();
    void shouldHaveAuthTokenIdentifierPerConfig();
    void shouldSaveAndLoadSettings();
};
