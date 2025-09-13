/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QtCore/QObject>

class TextAutoGenerateTextToolPluginPropertyTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolPluginPropertyTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolPluginPropertyTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
