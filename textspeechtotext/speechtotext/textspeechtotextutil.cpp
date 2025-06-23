/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textspeechtotextutil.h"
using namespace Qt::Literals::StringLiterals;

using namespace TextSpeechToText;
QString TextSpeechToTextUtil::groupTranslateName()
{
    return u"TextToSpeech"_s;
}

QString TextSpeechToTextUtil::engineTextToSpeechName()
{
    return u"engine"_s;
}

QString TextSpeechToTextUtil::defaultEngineName()
{
    return {};
}
