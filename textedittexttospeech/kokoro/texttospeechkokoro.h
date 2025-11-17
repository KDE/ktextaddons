/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textedittexttospeech_export.h"
#include <QObject>
namespace TextEditTextToSpeech
{
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechKokoro : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoro(QObject *parent = nullptr);
    ~TextToSpeechKokoro() override;
};
}
