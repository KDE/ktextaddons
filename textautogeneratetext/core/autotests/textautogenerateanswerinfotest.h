/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateAnswerInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAnswerInfoTest(QObject *parent = nullptr);
    ~TextAutoGenerateAnswerInfoTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldSaveLoadAnswerInfo();
};
