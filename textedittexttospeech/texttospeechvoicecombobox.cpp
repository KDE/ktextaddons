/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechvoicecombobox.h"
#include <QDebug>
using namespace TextEditTextToSpeech;

TextToSpeechVoiceComboBox::TextToSpeechVoiceComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

TextToSpeechVoiceComboBox::~TextToSpeechVoiceComboBox() = default;

QVoice TextToSpeechVoiceComboBox::currentVoice() const
{
    return currentData().value<QVoice>();
}

void TextToSpeechVoiceComboBox::setCurrentVoice(const QVoice &voice)
{
    const int index = findData(QVariant::fromValue(voice));
    qDebug() << " count " << count();
    qDebug() << " index " << index;
    if (index != -1) {
        setCurrentIndex(index);
    }
}

void TextToSpeechVoiceComboBox::updateVoices(const QVector<QVoice> &voices)
{
    clear();
    for (const QVoice &voice : voices) {
        addItem(voice.name(), QVariant::fromValue(voice));
    }
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
    // Sort it after loading list.
    model()->sort(0, Qt::AscendingOrder);
}

#include "moc_texttospeechvoicecombobox.cpp"
