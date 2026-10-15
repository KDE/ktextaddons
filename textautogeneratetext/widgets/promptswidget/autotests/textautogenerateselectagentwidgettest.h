/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateSelectAgentWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectAgentWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateSelectAgentWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
