/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ExtractLanguageJobTest : public QObject
{
    Q_OBJECT
public:
    explicit ExtractLanguageJobTest(QObject *parent = nullptr);
    ~ExtractLanguageJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
