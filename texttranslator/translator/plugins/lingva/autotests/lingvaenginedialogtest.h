/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LingvaEngineDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit LingvaEngineDialogTest(QObject *parent = nullptr);
    ~LingvaEngineDialogTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
