/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolURLElicitationRequiredErrorTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolURLElicitationRequiredErrorTest(QObject *parent = nullptr);
    ~McpProtocolURLElicitationRequiredErrorTest() override = default;

private Q_SLOTS:
    void shouldLoadAndSaveError();
    void shouldRejectOtherErrorCode();
};
