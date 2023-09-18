/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechvoicecombobox.h"
using namespace TextEditTextToSpeech;
TextToSpeechVoiceComboBox::TextToSpeechVoiceComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

TextToSpeechVoiceComboBox::~TextToSpeechVoiceComboBox() = default;

QVoice TextToSpeechVoiceComboBox::currentVoice() const
{
    return {};
}

void TextToSpeechVoiceComboBox::updateVoices(const QVector<QVoice> &voices)
{
    clear();
    for (const QVoice &voice : voices) {
        // TODO store voice
        addItem(voice.name(), voice.name());
    }
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

#include "moc_texttospeechvoicecombobox.cpp"
