/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTextInstanceTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstanceTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstanceTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
