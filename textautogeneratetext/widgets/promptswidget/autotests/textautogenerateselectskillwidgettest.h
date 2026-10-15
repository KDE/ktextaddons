/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateSelectSkillWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectSkillWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateSelectSkillWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
