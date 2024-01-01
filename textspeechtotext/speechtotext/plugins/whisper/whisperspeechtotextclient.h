/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextclient.h"

class WhisperSpeechToTextClient : public TextSpeechToText::SpeechToTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.texttospeech.whisper")
    Q_INTERFACES(TextSpeechToText::SpeechToTextClient)
public:
    explicit WhisperSpeechToTextClient(QObject *parent = nullptr);
    ~WhisperSpeechToTextClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;

    [[nodiscard]] TextSpeechToText::SpeechToTextClient::EngineType engineType() const override;

    [[nodiscard]] TextSpeechToText::SpeechToTextPlugin *createTextToSpeech() override;
};
