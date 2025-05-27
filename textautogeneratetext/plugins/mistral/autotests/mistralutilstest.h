/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MistralUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit MistralUtilsTest(QObject *parent = nullptr);
    ~MistralUtilsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
