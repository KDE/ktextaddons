/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutogenerateHistoryListViewTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateHistoryListViewTest(QObject *parent = nullptr);
    ~TextAutogenerateHistoryListViewTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
