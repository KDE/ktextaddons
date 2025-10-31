/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechutil.h"

#include <KConfig>
#include <KConfigGroup>
#include <QIODevice>

using namespace Qt::Literals::StringLiterals;
QString TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName()
{
    return u"texttospeechrc"_s;
}

QString TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName()
{
    return u"Settings"_s;
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
    QByteArray ba = grp.readEntry("voice", QByteArray());
    QDataStream s(&ba, QIODevice::ReadOnly);
    s.setVersion(QDataStream::Qt_5_15);
    s >> settings.voice;
    return settings;
}

void TextEditTextToSpeech::TextToSpeechUtil::writeConfig(const TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings &settings)
{
    KConfig config(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName());
    KConfigGroup grp = config.group(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName());
    grp.writeEntry("volume", settings.volumeValue);
    grp.writeEntry("rate", settings.rate);
    grp.writeEntry("pitch", settings.pitch);
    grp.writeEntry("localeName", settings.localeName);
    // qDebug() << " engineName " << engineName;
    grp.writeEntry("engine", settings.engineName);
    QByteArray ba;
    QDataStream s(&ba, QIODevice::WriteOnly);
    s.setVersion(QDataStream::Qt_5_15);
    s << settings.voice;
    grp.writeEntry("voice", ba);
}

QDebug operator<<(QDebug d, const TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings &t)
{
    d << "voice " << t.voice;
    d << "engineName " << t.engineName;
    d << "localeName " << t.localeName;
    d << "rate " << t.rate;
    d << "pitch " << t.pitch;
    d << "volumeValue " << t.volumeValue;
    return d;
}
