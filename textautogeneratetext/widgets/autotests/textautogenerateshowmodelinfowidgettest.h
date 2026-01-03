/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateShowModelInfoWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowModelInfoWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateShowModelInfoWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
