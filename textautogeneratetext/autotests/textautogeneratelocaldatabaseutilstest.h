/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateLocalDatabaseUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateLocalDatabaseUtilsTest(QObject *parent = nullptr);
    ~TextAutoGenerateLocalDatabaseUtilsTest() override = default;
private Q_SLOTS:
    void shouldCheckPath();
    void shouldCheckDataBase();
};
