/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroutils.h"

#include <QDir>
#include <QFontMetrics>
#include <QPainter>
#include <QPixmap>
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

// The icons are generated once for the whole list of voices, a small square is
// enough for a combobox.
constexpr int s_iconSize = 32;

// "FR" -> the two regional indicator symbols the emoji fonts draw as a flag.
[[nodiscard]] QString flagEmoji(const QLocale &locale)
{
    const QString territory = QLocale::territoryToCode(locale.territory());
    if (territory.size() != 2) {
        return {};
    }
    QString flag;
    for (const QChar letter : territory) {
        flag += QChar::fromUcs4(0x1f1e6 + letter.toUpper().unicode() - u'A');
    }
    return flag;
}

// Without an emoji font the regional indicators are drawn as two boxes.
[[nodiscard]] bool canDrawText(const QFont &font, const QString &text)
{
    const QFontMetrics metrics(font);
    const QList<uint> codePoints = text.toUcs4();
    for (const uint codePoint : codePoints) {
        if (!metrics.inFontUcs4(codePoint)) {
            return false;
        }
    }
    return true;
}

void drawLocale(QPainter *painter, QRect rect, const QLocale &locale)
{
    QFont font = painter->font();
    font.setPixelSize(rect.height() * 3 / 4);
    const QString flag = flagEmoji(locale);
    if (!flag.isEmpty() && canDrawText(font, flag)) {
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignHCenter | Qt::AlignTop, flag);
        return;
    }
    // No emoji font: the country code inside a badge says the same thing.
    const QString territory = QLocale::territoryToCode(locale.territory());
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0x31, 0x63, 0x9c));
    painter->drawRoundedRect(rect.adjusted(0, rect.height() / 8, 0, -rect.height() / 4), 3, 3);
    font.setPixelSize(rect.height() / 2);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignTop, territory);
}

void drawGender(QPainter *painter, QRect rect, QVoice::Gender gender)
{
    QString symbol;
    QColor color;
    switch (gender) {
    case QVoice::Female:
        symbol = u"\u2640"_s; // ♀
        color = QColor(0xd8, 0x1b, 0x60);
        break;
    case QVoice::Male:
        symbol = u"\u2642"_s; // ♂
        color = QColor(0x1e, 0x88, 0xe5);
        break;
    case QVoice::Unknown:
        return;
    }
    // A filled disc keeps the symbol readable on top of the flag, whatever the
    // colors of the theme are.
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(rect);

    QFont font = painter->font();
    font.setPixelSize(rect.height() * 3 / 4);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(rect, Qt::AlignCenter, symbol);
}

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

QIcon TextEditTextToSpeech::TextToSpeechKokoroUtils::voiceIcon(const KokoroVoice &voice)
{
    QPixmap pixmap(s_iconSize, s_iconSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    drawLocale(&painter, QRect(0, 0, s_iconSize, s_iconSize), voice.locale);
    const int badgeSize = s_iconSize / 2;
    drawGender(&painter, QRect(s_iconSize - badgeSize, s_iconSize - badgeSize, badgeSize, badgeSize), voice.gender);
    painter.end();
    return QIcon(pixmap);
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

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPath()
{
    const QString path = QDir::homePath() + u"/.venv/kokoro"_s;
    return path;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPython()
{
    const QString python = TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPath() + u"/bin/python"_s;
    return python;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPip()
{
    const QString pip = TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPath() + u"/bin/pip"_s;
    return pip;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::venvPip()
{
    // The pip of the venv, so that the modules are installed in it and not system wide.
    const QString pip = TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPip();
    return QFileInfo::exists(pip) ? pip : QString();
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::venvPython()
{
    // We install in venv => for the moment kokoro doesn't work with 3.13 (only 3.11)
    const QString python = TextEditTextToSpeech::TextToSpeechKokoroUtils::defaultVenvPython(); // Verify windows/macos
    return QFileInfo::exists(python) ? python : QString();
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonVersion()
{
    return u"python3.11"_s;
}

QString TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonVersionPath()
{
    const QString path = QStandardPaths::findExecutable(TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonVersion());
    return path;
}
