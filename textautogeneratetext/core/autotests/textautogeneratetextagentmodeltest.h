/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTextAgentModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextAgentModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextAgentModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldSetAgents();
    void shouldAddAgent();
    void shouldRemoveAgent();
    void shouldUpdateAgent();
};
