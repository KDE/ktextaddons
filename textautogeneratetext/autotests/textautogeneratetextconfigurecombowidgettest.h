/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutogenerateTextConfigureComboWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextConfigureComboWidgetTest(QObject *parent = nullptr);
    ~TextAutogenerateTextConfigureComboWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
