/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextplugin.h"

class GoogleSpeechToTextPlugin : public TextSpeechToText::SpeechToTextPlugin
{
    Q_OBJECT
public:
    explicit GoogleSpeechToTextPlugin(QObject *parent = nullptr);
    ~GoogleSpeechToTextPlugin() override;

    void speechToText() override;
};