/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTextConfigureMcpServersWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextConfigureMcpServersWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextConfigureMcpServersWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldApplyChangesWhenSaved();
};
