/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextclient.h"

class GoogleSpeechToTextClient : public TextSpeechToText::SpeechToTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.texttospeech.google")
    Q_INTERFACES(TextSpeechToText::SpeechToTextClient)
public:
    explicit GoogleSpeechToTextClient(QObject *parent = nullptr);
    ~GoogleSpeechToTextClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;

    [[nodiscard]] TextSpeechToText::SpeechToTextClient::EngineType engineType() const override;

    [[nodiscard]] TextSpeechToText::SpeechToTextPlugin *createTextToSpeech() override;
};
