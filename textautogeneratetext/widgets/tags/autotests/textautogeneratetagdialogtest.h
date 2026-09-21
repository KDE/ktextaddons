/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTagDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTagDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateTagDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEnableOkButtonWhenNameIsNotEmpty();
};
