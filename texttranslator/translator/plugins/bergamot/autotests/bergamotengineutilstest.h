/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class BergamotEngineUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit BergamotEngineUtilsTest(QObject *parent = nullptr);
    ~BergamotEngineUtilsTest() override = default;
private Q_SLOTS:
    void shouldDefaultBergamotRepository();
    void shouldExtractInfoFromLanguageLocallyStored();
};
