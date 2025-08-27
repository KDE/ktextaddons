/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTextInstancesManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManagerTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstancesManagerTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAddInstances();
    void shouldRemoveInstances();
};
