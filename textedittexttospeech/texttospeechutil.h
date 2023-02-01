/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textedittexttospeech_private_export.h"
#include <QObject>
namespace TextEditTextToSpeech
{
namespace TextToSpeechUtil
{
Q_REQUIRED_RESULT TEXTEDITTEXTTOSPEECH_TESTS_EXPORT QString textToSpeechConfigFileName();
Q_REQUIRED_RESULT TEXTEDITTEXTTOSPEECH_TESTS_EXPORT QString textToSpeechConfigGroupName();
};
}
