/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokorocheckjob.h"
#include "texttospeech_kokoro_lib_debug.h"
#include "texttospeechkokoroutils.h"

using namespace TextEditTextToSpeech;
TextToSpeechKokoroCheckJob::TextToSpeechKokoroCheckJob(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoroCheckJob::~TextToSpeechKokoroCheckJob() = default;

bool TextToSpeechKokoroCheckJob::canStart() const
{
    return TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonScriptPath().isEmpty();
}

void TextToSpeechKokoroCheckJob::start()
{
    if (!canStart()) {
        deleteLater();
        qCWarning(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Impossible to start TextToSpeechKokoroCheckJob";
        return;
    }
    // TODO
}
#include "moc_texttospeechkokorocheckjob.cpp"
