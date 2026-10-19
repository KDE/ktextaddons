/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolServerConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServerConfigureWidgetTest(QObject *parent = nullptr);
    ~McpProtocolServerConfigureWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldGenerateTokenWhenRequireAuthentication();
    void shouldLoadSettings();
    void shouldValidateUrl_data();
    void shouldValidateUrl();
};
