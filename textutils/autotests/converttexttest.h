/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConvertTextTest : public QObject
{
    Q_OBJECT
public:
    explicit ConvertTextTest(QObject *parent = nullptr);
    ~ConvertTextTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};