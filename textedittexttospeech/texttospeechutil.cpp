/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechutil.h"

#include <KConfig>
#include <KConfigGroup>

QString TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName()
{
    return QStringLiteral("texttospeechrc");
}

QString TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName()
{
    return QStringLiteral("Settings");
}

TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings TextEditTextToSpeech::TextToSpeechUtil::loadSettings()
{
    TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings settings;
    KConfig config(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName());
    const KConfigGroup grp = config.group(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName());
    settings.engineName = grp.readEntry("engine");
    settings.rate = grp.readEntry("rate", 50);
    settings.volumeValue = grp.readEntry("volume", 0);
    settings.localeName = grp.readEntry("localeName");
    settings.pitch = grp.readEntry("pitch", 0);
    return settings;
}
