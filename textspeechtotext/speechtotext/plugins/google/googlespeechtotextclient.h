/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotext/speechtotextclient.h"

class GoogleSpeechToTextClient : public TextSpeechToText::SpeechToTextClient
{
    Q_OBJECT
public:
    explicit GoogleSpeechToTextClient(QObject *parent = nullptr);
    ~GoogleSpeechToTextClient() override;
};
