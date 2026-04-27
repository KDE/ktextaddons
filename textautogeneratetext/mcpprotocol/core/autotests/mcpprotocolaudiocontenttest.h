/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolAudioContentTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolAudioContentTest(QObject *parent = nullptr);
    ~McpProtocolAudioContentTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
