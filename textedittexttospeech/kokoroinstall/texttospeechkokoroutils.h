/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "kokoroinstalltexttospeech_export.h"
#include <QLocale>
#include <QVoice>

namespace TextEditTextToSpeech
{
namespace TextToSpeechKokoroUtils
{
/*!
 * \class TextEditTextToSpeech::TextToSpeechKokoroUtils::KokoroVoice
 *
 * \brief Describes one of the voices shipped with the Kokoro model.
 *
 * A Kokoro voice identifier encodes the language in its first character and the
 * gender in the second one, "ff_siwis" being the french female voice "Siwis".
 * The identifier is what has to be handed over to the backend.
 */
struct KokoroVoice {
    QString identifier; /*!< The name used by the model, for example "ff_siwis" */
    QString name; /*!< The name shown to the user, for example "Siwis" */
    QLocale locale;
    QVoice::Gender gender = QVoice::Unknown;
    bool needsExtraG2p = false; /*!< Japanese and Chinese need misaki[ja]/misaki[zh] */
};

/*! Selects the languages exposed by the functions below. */
enum class VoiceFilter {
    EspeakSupported, /*!< Skip the voices espeak-ng cannot phonemize */
    All, /*!< Every voice of the model, japanese and chinese included */
};

/*! Returns the voices of the model, as plain data. */
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QList<KokoroVoice> kokoroVoices(VoiceFilter filter = VoiceFilter::EspeakSupported);

/*! Returns the locales covered by the voices, without duplicates. */
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QList<QLocale> availableLocales(VoiceFilter filter = VoiceFilter::EspeakSupported);

/*! Returns the lang_code expected by KPipeline for \a identifier, for example "f" for "ff_siwis". */
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString languageCode(const QString &identifier);

[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString pythonScript();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString pythonScriptPath();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString venvPython();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString defaultVenvPath();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString defaultVenvPython();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString defaultVenvPip();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString venvPip();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString pythonVersion();
[[nodiscard]] KOKOROINSTALLTEXTTOSPEECH_EXPORT QString pythonVersionPath();
}
}
