/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateLocalDatabaseManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateLocalDatabaseManagerTest(QObject *parent = nullptr);
    ~TextAutoGenerateLocalDatabaseManagerTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAddRemoveEphemeral();
};
