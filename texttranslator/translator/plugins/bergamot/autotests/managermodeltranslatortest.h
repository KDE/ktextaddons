/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ManagerModelTranslatorTest : public QObject
{
    Q_OBJECT
public:
    explicit ManagerModelTranslatorTest(QObject *parent = nullptr);
    ~ManagerModelTranslatorTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldParseJson();
    void shouldParseJson_data();
};
