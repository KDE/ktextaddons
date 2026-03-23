/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolListResourcesRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolListResourcesRequestTest(QObject *parent = nullptr);
    ~McpProtocolListResourcesRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
