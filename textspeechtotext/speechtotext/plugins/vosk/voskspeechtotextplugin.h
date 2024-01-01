/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextplugin.h"
class VoskSpeechToTextDevice;
class VoskSpeechToTextPlugin : public TextSpeechToText::SpeechToTextPlugin
{
    Q_OBJECT
public:
    explicit VoskSpeechToTextPlugin(QObject *parent = nullptr);
    ~VoskSpeechToTextPlugin() override;

    void speechToText() override;

    [[nodiscard]] int sampleRate() const override;

    [[nodiscard]] QIODevice *audioDevice() const override;

    [[nodiscard]] bool loadSettings() override;
    void clear() override;

private:
    VoskSpeechToTextDevice *const mDevice;
};
