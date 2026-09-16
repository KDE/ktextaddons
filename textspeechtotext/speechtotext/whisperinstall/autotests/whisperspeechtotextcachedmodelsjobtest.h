/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextCachedModelsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextCachedModelsJobTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextCachedModelsJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldOnlyKeepTheCachedModels();
    void shouldNotParseInvalidOutput();
    void shouldAskTheScript();
};
