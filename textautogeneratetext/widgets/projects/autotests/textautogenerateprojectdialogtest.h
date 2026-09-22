/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateProjectDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateProjectDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateProjectDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEnableOkButtonWhenNameIsNotEmpty();
};
