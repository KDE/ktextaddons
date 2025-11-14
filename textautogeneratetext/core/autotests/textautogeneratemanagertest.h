/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManagerTest(QObject *parent = nullptr);
    ~TextAutoGenerateManagerTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldIsFavorite();
    void shouldSetDebug();
};
