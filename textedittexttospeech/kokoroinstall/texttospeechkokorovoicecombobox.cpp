/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokorovoicecombobox.h"
#include "texttospeechkokoroutils.h"
#include <KLocalizedString>

using namespace TextEditTextToSpeech;

namespace
{
[[nodiscard]] QString genderName(QVoice::Gender gender)
{
    switch (gender) {
    case QVoice::Female:
        return i18nc("@item:intext gender of a voice", "Female");
    case QVoice::Male:
        return i18nc("@item:intext gender of a voice", "Male");
    case QVoice::Unknown:
        break;
    }
    return i18nc("@item:intext gender of a voice", "Unknown");
}

// "English (United States)": the language alone would not separate the
// american voices from the british ones.
[[nodiscard]] QString localeName(const QLocale &locale)
{
    return i18nc("@item:intext <language> (<country>)",
                 "%1 (%2)",
                 QLocale::languageToString(locale.language()),
                 QLocale::territoryToString(locale.territory()));
}
}

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
        addItem(TextToSpeechKokoroUtils::voiceIcon(voice), i18nc("@info:tooltip <voice name> (<gender>)", "%1 (%2)", voice.name, genderName(voice.gender)));
        setItemData(count() - 1,
                    i18nc("@info:tooltip <voice name> (<language>, <gender>)", "%1 (%2, %3)", voice.name, localeName(voice.locale), genderName(voice.gender)),
                    Qt::ToolTipRole);
    }
}

QString TextToSpeechKokoroVoiceComboBox::currentVoice() const
{
    return currentData().toString();
}

#include "moc_texttospeechkokorovoicecombobox.cpp"
