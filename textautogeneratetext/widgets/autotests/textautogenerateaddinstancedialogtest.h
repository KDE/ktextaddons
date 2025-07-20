/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateAddInstanceDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAddInstanceDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateAddInstanceDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
