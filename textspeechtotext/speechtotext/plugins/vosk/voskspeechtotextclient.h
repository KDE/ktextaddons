/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextclient.h"

class VoskSpeechToTextClient : public TextSpeechToText::SpeechToTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.texttospeech.vosk")
    Q_INTERFACES(TextSpeechToText::SpeechToTextClient)
public:
    explicit VoskSpeechToTextClient(QObject *parent = nullptr);
    ~VoskSpeechToTextClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;

    [[nodiscard]] TextSpeechToText::SpeechToTextClient::EngineType engineType() const override;

    [[nodiscard]] TextSpeechToText::SpeechToTextPlugin *createTextToSpeech() override;

    [[nodiscard]] bool hasConfigurationDialog() const override;
    [[nodiscard]] bool showConfigureDialog(QWidget *parentWidget) override;
};
