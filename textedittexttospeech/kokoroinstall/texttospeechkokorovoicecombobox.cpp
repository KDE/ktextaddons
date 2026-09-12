/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokorovoicecombobox.h"
#include "texttospeechkokoroutils.h"
#include <KLocalizedString>

using namespace TextEditTextToSpeech;
TextToSpeechKokoroVoiceComboBox::TextToSpeechKokoroVoiceComboBox(QWidget *parent)
    : QComboBox(parent)
{
    fill();
}

TextToSpeechKokoroVoiceComboBox::~TextToSpeechKokoroVoiceComboBox() = default;

void TextToSpeechKokoroVoiceComboBox::fill()
{
    const QList<TextToSpeechKokoroUtils::KokoroVoice> listVoices = TextToSpeechKokoroUtils::kokoroVoices();
    for (const auto &voice : listVoices) {
        // TODO add icon from local + gender
        addItem(voice.name, voice.name);
    }
}

#include "moc_texttospeechkokorovoicecombobox.cpp"
