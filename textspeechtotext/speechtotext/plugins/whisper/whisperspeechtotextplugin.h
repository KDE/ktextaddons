/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextplugin.h"

class WhisperSpeechToTextPlugin : public TextSpeechToText::SpeechToTextPlugin
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextPlugin(QObject *parent = nullptr);
    ~WhisperSpeechToTextPlugin() override;

    void speechToText() override;

    Q_REQUIRED_RESULT int sampleRate() const override;
    Q_REQUIRED_RESULT QString defaultLanguage() const override;
    Q_REQUIRED_RESULT QIODevice *audioDevice() const override;
};
