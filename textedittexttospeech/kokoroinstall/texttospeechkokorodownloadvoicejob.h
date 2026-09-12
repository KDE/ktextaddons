/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kokoroinstalltexttospeech_export.h"
#include <QObject>
#include <QStringList>
namespace TextEditTextToSpeech
{
class KOKOROINSTALLTEXTTOSPEECH_EXPORT TextToSpeechKokoroDownloadVoiceJob : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroDownloadVoiceJob(QObject *parent = nullptr);
    ~TextToSpeechKokoroDownloadVoiceJob() override;

Q_SIGNALS:
    void downloadDone();
};
}
