/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolGetPromptRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolGetPromptRequestTest(QObject *parent = nullptr);
    ~McpProtocolGetPromptRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
