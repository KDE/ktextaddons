/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTextPromptModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextPromptModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextPromptModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldSetPrompt();
    void shouldAddPrompt();
    void shouldRemovePrompt();
    void shouldUpdatePrompt();
};
