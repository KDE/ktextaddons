/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class OllamaLogDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaLogDialogTest(QObject *parent = nullptr);
    ~OllamaLogDialogTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};
