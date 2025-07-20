/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateHistoryListViewTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateHistoryListViewTest(QObject *parent = nullptr);
    ~TextAutoGenerateHistoryListViewTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
