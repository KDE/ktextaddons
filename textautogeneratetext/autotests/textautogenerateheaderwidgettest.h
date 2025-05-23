/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateHeaderWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHeaderWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateHeaderWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEmitNewChat();
    void shouldEmitChangeFavoriteRequested();
};
