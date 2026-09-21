/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTagTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTagTest(QObject *parent = nullptr);
    ~TextAutoGenerateTagTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
