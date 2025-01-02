/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TranslatorTest : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorTest(QObject *parent = nullptr);
    ~TranslatorTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldParseJson();
    void shouldParseJson_data();
};
