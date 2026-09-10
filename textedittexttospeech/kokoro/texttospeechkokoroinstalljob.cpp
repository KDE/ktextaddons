/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroinstalljob.h"
#include "texttospeech_kokoro_lib_debug.h"
using namespace TextEditTextToSpeech;
TextToSpeechKokoroInstallJob::TextToSpeechKokoroInstallJob(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoroInstallJob::~TextToSpeechKokoroInstallJob() = default;

bool TextToSpeechKokoroInstallJob::canStart() const
{
    return !mModules.isEmpty();
}

void TextToSpeechKokoroInstallJob::start()
{
    if (!canStart()) {
        // Q_EMIT needToReinstall();
        qCWarning(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Impossible to start TextToSpeechKokoroCheckJob";
        deleteLater();
        return;
    }
    // TODO
    deleteLater();
}

QStringList TextToSpeechKokoroInstallJob::modules() const
{
    return mModules;
}

void TextToSpeechKokoroInstallJob::setModules(const QStringList &newModules)
{
    mModules = newModules;
}

#include "moc_texttospeechkokoroinstalljob.cpp"
