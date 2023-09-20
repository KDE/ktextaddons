/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textedittexttospeech_private_export.h"
#include <QObject>
#include <QVoice>
namespace TextEditTextToSpeech
{
namespace TextToSpeechUtil
{
struct TextToSpeechSettings {
    QVoice voice;
    QString engineName;
    QString localeName;
    int rate = -1;
    int pitch = -1;
    int volumeValue = -1;
};

Q_REQUIRED_RESULT TEXTEDITTEXTTOSPEECH_TESTS_EXPORT QString textToSpeechConfigFileName();
Q_REQUIRED_RESULT TEXTEDITTEXTTOSPEECH_TESTS_EXPORT QString textToSpeechConfigGroupName();
Q_REQUIRED_RESULT TEXTEDITTEXTTOSPEECH_TESTS_EXPORT TextToSpeechSettings loadSettings();
};
}
