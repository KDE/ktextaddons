/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutogenerateHeaderWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateHeaderWidgetTest(QObject *parent = nullptr);
    ~TextAutogenerateHeaderWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
