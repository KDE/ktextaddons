/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateTextPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextPluginTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextPluginTest() override = default;

private Q_SLOTS:
    void shouldSendToLLMInfoDefaultValues();
};
