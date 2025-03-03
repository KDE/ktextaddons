/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutogenerateWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateWidgetTest(QObject *parent = nullptr);
    ~TextAutogenerateWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
