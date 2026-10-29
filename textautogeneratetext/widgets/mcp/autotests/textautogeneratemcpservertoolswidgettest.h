/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateMcpServerToolsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMcpServerToolsWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateMcpServerToolsWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldShowAllowedTools();
    void shouldChangeAllowedTools();
    void shouldFilterListOfTools();
};
