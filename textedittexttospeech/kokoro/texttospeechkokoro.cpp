/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoro.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechKokoro::TextToSpeechKokoro(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoro::~TextToSpeechKokoro() = default;

#include "moc_texttospeechkokoro.cpp"
