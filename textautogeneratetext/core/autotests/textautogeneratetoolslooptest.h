/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateToolsLoopTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolsLoopTest(QObject *parent = nullptr);
    ~TextAutoGenerateToolsLoopTest() override = default;

private Q_SLOTS:
    void shouldSendToolResultsToLLM();
    void shouldSendToolResultsInOllamaFormat();
    void shouldStopAfterTooManyToolCalls();
};
