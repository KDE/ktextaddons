/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textspeechtotextutil.h"

#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;
QString TextSpeechToTextUtil::groupTranslateName()
{
    return u"SpeechToText"_s;
}

QString TextSpeechToTextUtil::engineTextToSpeechName()
{
    return u"engine"_s;
}

QString TextSpeechToTextUtil::defaultEngineName()
{
    return {};
}

QString TextSpeechToTextUtil::soundGroupName()
{
    return u"Speech To Text"_s;
}

QString TextSpeechToTextUtil::loadEngineName()
{
    const KConfigGroup group(KSharedConfig::openConfig(), TextSpeechToTextUtil::groupTranslateName());
    return group.readEntry(TextSpeechToTextUtil::engineTextToSpeechName(), TextSpeechToTextUtil::defaultEngineName());
}

void TextSpeechToTextUtil::saveEngineName(const QString &engineName)
{
    KConfigGroup group(KSharedConfig::openConfig(), TextSpeechToTextUtil::groupTranslateName());
    if (engineName.isEmpty()) {
        group.deleteEntry(TextSpeechToTextUtil::engineTextToSpeechName());
    } else {
        group.writeEntry(TextSpeechToTextUtil::engineTextToSpeechName(), engineName);
    }
    group.sync();
}
