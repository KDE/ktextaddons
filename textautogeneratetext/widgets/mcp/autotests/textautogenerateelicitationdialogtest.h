/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateElicitationDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateElicitationDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateElicitationDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
