/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateSearchDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateSearchDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
