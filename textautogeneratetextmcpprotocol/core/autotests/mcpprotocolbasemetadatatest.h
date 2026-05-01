/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolBaseMetadataTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolBaseMetadataTest(QObject *parent = nullptr);
    ~McpProtocolBaseMetadataTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
