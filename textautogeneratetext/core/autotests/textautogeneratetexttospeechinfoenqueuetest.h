/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

class TextAutoGenerateTextToSpeechInfoEnqueueTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToSpeechInfoEnqueueTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextToSpeechInfoEnqueueTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
