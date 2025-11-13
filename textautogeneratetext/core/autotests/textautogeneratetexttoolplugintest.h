/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

class TextAutoGenerateTextToolPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolPluginTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolPluginTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldGenerateMetadata();
    void shouldGenerateMetadata_data();
    void shouldTextToolPluginInfoDefaultValues();
};
