/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class WhisperSpeechToTextPluginJob : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextPluginJob(QObject *parent = nullptr);
    ~WhisperSpeechToTextPluginJob() override;

    void start();
};
