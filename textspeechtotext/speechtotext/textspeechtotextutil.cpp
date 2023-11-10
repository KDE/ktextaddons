/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textspeechtotextutil.h"

using namespace TextSpeechToText;
QString TextSpeechToTextUtil::groupTranslateName()
{
    return QStringLiteral("TextToSpeech");
}

QString TextSpeechToTextUtil::engineTextToSpeechName()
{
    return QStringLiteral("engine");
}

QString TextSpeechToTextUtil::defaultEngineName()
{
    return {};
}
