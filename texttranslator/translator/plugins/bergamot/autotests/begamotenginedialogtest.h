/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class BegamotEngineDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit BegamotEngineDialogTest(QObject *parent = nullptr);
    ~BegamotEngineDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
