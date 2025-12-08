/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateShowImageWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateShowImageWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateShowImageWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
