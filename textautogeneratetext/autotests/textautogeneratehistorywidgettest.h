/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

class TextAutogenerateHistoryWidgetTest : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateHistoryWidgetTest(QWidget *parent = nullptr);
    ~TextAutogenerateHistoryWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
