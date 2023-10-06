/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class VoskSpeechToTextPluginJob : public QObject
{
    Q_OBJECT
public:
    explicit VoskSpeechToTextPluginJob(QObject *parent = nullptr);
    ~VoskSpeechToTextPluginJob() override;
};
