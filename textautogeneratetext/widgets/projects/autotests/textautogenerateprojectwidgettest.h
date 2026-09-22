/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateProjectWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateProjectWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateProjectWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldKeepIdentifierWhenEditingProject();
    void shouldEmitEnableOkButton();
};
