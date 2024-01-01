
/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QObject>

class GenerateInstalledLanguageInfoJobTest : public QObject
{
    Q_OBJECT
public:
    explicit GenerateInstalledLanguageInfoJobTest(QObject *parent = nullptr);
    ~GenerateInstalledLanguageInfoJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
