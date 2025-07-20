/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateAddInstanceWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAddInstanceWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateAddInstanceWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
