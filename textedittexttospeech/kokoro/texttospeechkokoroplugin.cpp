/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroplugin.h"
#include "texttospeechkokoroengine.h"

using namespace TextEditTextToSpeech;

QTextToSpeechEngine *TextToSpeechKokoroPlugin::createTextToSpeechEngine(const QVariantMap &parameters, QObject *parent, QString *errorString) const
{
    Q_UNUSED(errorString);
    return new TextToSpeechKokoroEngine(parameters, parent);
}
