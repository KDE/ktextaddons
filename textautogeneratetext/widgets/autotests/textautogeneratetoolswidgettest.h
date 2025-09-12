/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateToolsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolsWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateToolsWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
