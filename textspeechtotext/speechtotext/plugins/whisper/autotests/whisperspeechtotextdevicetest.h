/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextDeviceTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextDeviceTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextDeviceTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAssignInfo();
    void shouldTakeCompleteFramesOnly();
    void shouldTakeSeveralFramesAtOnce();
    void shouldSkipTheDeclaredPayload();
    void shouldNotSendAudioWithoutBackend();
};
