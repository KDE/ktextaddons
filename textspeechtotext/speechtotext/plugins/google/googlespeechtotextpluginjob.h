/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GoogleSpeechToTextPluginJob : public QObject
{
    Q_OBJECT
public:
    explicit GoogleSpeechToTextPluginJob(QObject *parent = nullptr);
    ~GoogleSpeechToTextPluginJob() override;

    void start();
};
