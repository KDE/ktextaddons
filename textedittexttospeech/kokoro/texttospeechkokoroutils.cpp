/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroutils.h"

#include <QDir>
#include <QStandardPaths>
#include <array>

using namespace Qt::Literals::StringLiterals;

namespace
{
struct KokoroLanguage {
    char code; // The lang_code passed to KPipeline
    const char *localeName;
    bool needsExtraG2p;
};

// Kokoro derives the phonemes from espeak-ng, except for japanese and chinese
// which require misaki[ja] and misaki[zh].
constexpr std::array<KokoroLanguage, 9> s_languages{{
    {'a', "en_US", false},
    {'b', "en_GB", false},
    {'e', "es_ES", false},
    {'f', "fr_FR", false},
    {'h', "hi_IN", false},
    {'i', "it_IT", false},
    {'p', "pt_BR", false},
    {'j', "ja_JP", true},
    {'z', "zh_CN", true},
}};

// The 54 voices of Kokoro-82M. The first character gives the language, the
// second one the gender, so nothing else has to be stored here.
constexpr std::array<const char *, 54> s_voiceIdentifiers{
    "af_heart",    "af_alloy", "af_aoede",   "af_bella",  "af_jessica",  "af_kore",    "af_nicole",  "af_nova",  "af_river",  "af_sarah",      "af_sky",
    "am_adam",     "am_echo",  "am_eric",    "am_fenrir", "am_liam",     "am_michael", "am_onyx",    "am_puck",  "am_santa",  "bf_alice",      "bf_emma",
    "bf_isabella", "bf_lily",  "bm_daniel",  "bm_fable",  "bm_george",   "bm_lewis",   "ef_dora",    "em_alex",  "em_santa",  "ff_siwis",      "hf_alpha",
    "hf_beta",     "hm_omega", "hm_psi",     "if_sara",   "im_nicola",   "pf_dora",    "pm_alex",    "pm_santa", "jf_alpha",  "jf_gongitsune", "jf_nezumi",
    "jf_tebukuro", "jm_kumo",  "zf_xiaobei", "zf_xiaoni", "zf_xiaoxiao", "zf_xiaoyi",  "zm_yunjian", "zm_yunxi", "zm_yunxia", "zm_yunyang",
};

[[nodiscard]] const KokoroLanguage *languageForIdentifier(QStringView identifier)
{
    if (identifier.size() < 2 || identifier.at(0).unicode() > 0x7f) {
        return nullptr;
    }
    const char code = identifier.at(0).toLatin1();
    for (const KokoroLanguage &language : s_languages) {
        if (language.code == code) {
            return &language;
        }
    }
    return nullptr;
}

[[nodiscard]] bool isFiltered(const KokoroLanguage &language, TextEditTextToSpeech::TextToSpeechKokoroUtils::VoiceFilter filter)
{
    return language.needsExtraG2p && filter == TextEditTextToSpeech::TextToSpeechKokoroUtils::VoiceFilter::EspeakSupported;
}

// "ff_siwis" -> "Siwis"
[[nodiscard]] QString displayName(QStringView identifier)
{
    const qsizetype separator = identifier.indexOf(u'_');
    if (separator == -1 || separator + 1 >= identifier.size()) {
        return identifier.toString();
    }
    QString name = identifier.sliced(separator + 1).toString();
    name[0] = name.at(0).toUpper();
    return name;
}
}

QList<TextEditTextToSpeech::TextToSpeechKokoroUtils::KokoroVoice> TextEditTextToSpeech::TextToSpeechKokoroUtils::kokoroVoices(VoiceFilter filter)
{
    QList<KokoroVoice> voices;
    voices.reserve(s_voiceIdentifiers.size());
    for (const char *rawIdentifier : s_voiceIdentifiers) {
        const QString identifier = QString::fromLatin1(rawIdentifier);
        const KokoroLanguage *language = languageForIdentifier(identifier);
        if (!language || isFiltered(*language, filter)) {
            continue;
        }
        KokoroVoice voice;
        voice.identifier = identifier;
        voice.name = displayName(identifier);
        voice.locale = QLocale(QString::fromLatin1(language->localeName));
        voice.gender = (identifier.at(1) == u'f') ? QVoice::Female : QVoice::Male;
        voice.needsExtraG2p = language->needsExtraG2p;
        voices.append(std::move(voice));
    }
    return voices;
}

QList<QLocale> TextEditTextToSpeech::TextToSpeechKokoroUtils::availableLocales(VoiceFilter filter)
{
    QList<QLocale> locales;
    locales.reserve(s_languages.size());
    for (const KokoroLanguage &language : s_languages) {
        if (isFiltered(language, filter)) {
            continue;
        }
        // One locale per language code, so there is nothing to deduplicate.
        locales.append(QLocale(QString::fromLatin1(language.localeName)));
    }
    return locales;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::languageCode(const QString &identifier)
{
    const KokoroLanguage *language = languageForIdentifier(identifier);
    return language ? QString(QLatin1Char(language->code)) : QString();
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonScript()
{
    return u"kokoro_helper.py"_s;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonScriptPath()
{
    const QString path = QStandardPaths::findExecutable(TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonScript());
    return path;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPython()
{
    const QString python = QDir::homePath() + u"/.venv/kokoro/bin/python"_s;
    return python;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::venvPython()
{
    // We install in venv => for the moment kokoro doesn't work with 3.13 (only 3.11)
    const QString python = TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPython(); // Verify windows/macos
    return QFileInfo::exists(python) ? python : QString();
}
