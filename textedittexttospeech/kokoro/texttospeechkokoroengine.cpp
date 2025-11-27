/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroengine.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechKokoroEngine::TextToSpeechKokoroEngine(const QVariantMap &parameters, QObject *parent)
    : QTextToSpeechEngine(parent)
{
}

TextToSpeechKokoroEngine::~TextToSpeechKokoroEngine() = default;
