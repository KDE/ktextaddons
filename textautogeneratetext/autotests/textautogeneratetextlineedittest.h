/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateTextLineEditTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextLineEditTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextLineEditTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
