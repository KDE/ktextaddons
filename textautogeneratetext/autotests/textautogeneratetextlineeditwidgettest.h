/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutogenerateTextLineEditWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextLineEditWidgetTest(QObject *parent = nullptr);
    ~TextAutogenerateTextLineEditWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEnableButton();
};
