/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroplugin.h"
#include "texttospeechkokoroengine.h"

using namespace TextEditTextToSpeech;

QTextToSpeechEngine *
TextToSpeechKokoroPlugin::createTextToSpeechEngine(const QVariantMap &parameters, QObject *parent, [[maybe_unused]] QString *errorString) const
{
    return new TextToSpeechKokoroEngine(parameters, parent);
}
