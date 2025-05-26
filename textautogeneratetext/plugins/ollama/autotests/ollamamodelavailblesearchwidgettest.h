/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaModelAvailbleSearchWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelAvailbleSearchWidgetTest(QObject *parent = nullptr);
    ~OllamaModelAvailbleSearchWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEmitSearchText();
};
