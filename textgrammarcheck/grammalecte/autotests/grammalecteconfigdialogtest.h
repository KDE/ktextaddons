/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GrammalecteConfigDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteConfigDialogTest(QObject *parent = nullptr);
    ~GrammalecteConfigDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
