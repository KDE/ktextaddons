/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class BergamotEngineSettingsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit BergamotEngineSettingsWidgetTest(QObject *parent = nullptr);
    ~BergamotEngineSettingsWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
