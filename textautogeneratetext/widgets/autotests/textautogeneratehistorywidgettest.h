/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

class TextAutoGenerateHistoryWidgetTest : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistoryWidgetTest(QWidget *parent = nullptr);
    ~TextAutoGenerateHistoryWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
