/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolListPromptsResultTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolListPromptsResultTest(QObject *parent = nullptr);
    ~McpProtocolListPromptsResultTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
