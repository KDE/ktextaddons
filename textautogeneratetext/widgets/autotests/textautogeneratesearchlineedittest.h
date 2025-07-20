/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateSearchLineEditTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchLineEditTest(QObject *parent = nullptr);
    ~TextAutoGenerateSearchLineEditTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
