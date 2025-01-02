/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class BergamotEngineLanguageWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit BergamotEngineLanguageWidgetTest(QObject *parent = nullptr);
    ~BergamotEngineLanguageWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
