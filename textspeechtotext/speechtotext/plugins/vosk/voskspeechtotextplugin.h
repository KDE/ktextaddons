/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextplugin.h"

class VoskSpeechToTextPlugin : public TextSpeechToText::SpeechToTextPlugin
{
    Q_OBJECT
public:
    explicit VoskSpeechToTextPlugin(QObject *parent = nullptr);
    ~VoskSpeechToTextPlugin() override;

    void speechToText() override;

    Q_REQUIRED_RESULT int sampleRate() const override;
};
