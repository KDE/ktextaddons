/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaModelListViewTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelListViewTest(QObject *parent = nullptr);
    ~OllamaModelListViewTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
