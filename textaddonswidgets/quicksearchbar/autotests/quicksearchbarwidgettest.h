/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class QuickSearchBarWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickSearchBarWidgetTest(QObject *parent = nullptr);
    ~QuickSearchBarWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEmitSearchTextRequested();
};
