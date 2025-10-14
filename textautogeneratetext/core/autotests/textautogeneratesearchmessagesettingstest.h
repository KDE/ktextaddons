/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

class TextAutoGenerateSearchMessageSettingsTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchMessageSettingsTest(QObject *parent = nullptr);
    ~TextAutoGenerateSearchMessageSettingsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldClear();
};
