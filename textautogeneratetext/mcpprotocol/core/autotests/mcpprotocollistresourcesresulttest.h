/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolListResourcesResultTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolListResourcesResultTest(QObject *parent = nullptr);
    ~McpProtocolListResourcesResultTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
