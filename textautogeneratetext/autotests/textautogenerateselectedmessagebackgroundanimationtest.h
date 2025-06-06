/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateSelectedMessageBackgroundAnimationTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectedMessageBackgroundAnimationTest(QObject *parent = nullptr);
    ~TextAutoGenerateSelectedMessageBackgroundAnimationTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEmitBackgroundColorChanged();
};
