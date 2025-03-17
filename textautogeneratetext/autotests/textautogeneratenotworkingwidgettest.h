/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutogenerateNotWorkingWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateNotWorkingWidgetTest(QObject *parent = nullptr);
    ~TextAutogenerateNotWorkingWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
