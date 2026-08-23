/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

class TextAutoGenerateTextToSpeechEnqueueManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToSpeechEnqueueManagerTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextToSpeechEnqueueManagerTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldInsertAndKeepIndex();
    void shouldNotContainsInvalidInfo();
    void shouldRemoveLastOnly();
    void shouldClearList();
};
