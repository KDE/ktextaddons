/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class OllamaCommonModelAvailableInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableInfoTest(QObject *parent = nullptr);
    ~OllamaCommonModelAvailableInfoTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
