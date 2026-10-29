/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolUnsupportedProtocolVersionErrorTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolUnsupportedProtocolVersionErrorTest(QObject *parent = nullptr);
    ~McpProtocolUnsupportedProtocolVersionErrorTest() override = default;

private Q_SLOTS:
    void shouldLoadAndSaveError();
    void shouldRejectOtherErrorCode();
    void shouldRejectMissingRequiredFields();
    void shouldReturnSupportedAndRequested();
};
