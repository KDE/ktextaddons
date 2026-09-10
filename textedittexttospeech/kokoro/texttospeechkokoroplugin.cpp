/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroplugin.h"
#include "texttospeechkokorocheckjob.h"
#include "texttospeechkokoroengine.h"

using namespace TextEditTextToSpeech;

QTextToSpeechEngine *TextToSpeechKokoroPlugin::createTextToSpeechEngine(const QVariantMap &parameters, QObject *parent, QString *errorString) const
{
    // Make sure that it's sync
    if (const TextToSpeechKokoroCheckJob::CheckResult result = TextToSpeechKokoroCheckJob::checkSynchronously(); !result.isValid()) {
        if (errorString) {
            *errorString = result.errorString();
        }
        return nullptr;
    }
    return new TextToSpeechKokoroEngine(parameters, parent);
}

#include "moc_texttospeechkokoroplugin.cpp"
