/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaModelInstalledWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledWidgetTest(QObject *parent = nullptr);
    ~OllamaModelInstalledWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
