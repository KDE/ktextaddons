/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateConfigureWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateConfigureWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
