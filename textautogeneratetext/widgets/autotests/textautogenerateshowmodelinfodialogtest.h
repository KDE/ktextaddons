/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateShowModelInfoDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowModelInfoDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateShowModelInfoDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
