/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class OllamaModelInstalledInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledInfoTest(QObject *parent = nullptr);
    ~OllamaModelInstalledInfoTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldGenerateModelName_data();
    void shouldGenerateModelName();
};
