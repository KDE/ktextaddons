/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class VoskExtractLanguageJobTest : public QObject
{
    Q_OBJECT
public:
    explicit VoskExtractLanguageJobTest(QObject *parent = nullptr);
    ~VoskExtractLanguageJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
