/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGeneratePromptWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePromptWidgetTest(QObject *parent = nullptr);
    ~TextAutoGeneratePromptWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
