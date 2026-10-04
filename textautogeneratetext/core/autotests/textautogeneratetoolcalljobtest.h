/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateToolCallJobTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolCallJobTest(QObject *parent = nullptr);
    ~TextAutoGenerateToolCallJobTest() override = default;

private Q_SLOTS:
    void shouldNotStartWithoutInfo();
    void shouldCallSeveralTools();
    void shouldReportUnknownTool();
};
