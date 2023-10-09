/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT QString name() const override;
    Q_REQUIRED_RESULT QString translatedName() const override;

    Q_REQUIRED_RESULT TextSpeechToText::SpeechToTextClient::EngineType engineType() const override;

    Q_REQUIRED_RESULT TextSpeechToText::SpeechToTextPlugin *createTextToSpeech() override;

    Q_REQUIRED_RESULT bool hasConfigurationDialog() const override;
    Q_REQUIRED_RESULT bool showConfigureDialog(QWidget *parentWidget) override;
};
