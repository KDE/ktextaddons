/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QTextToSpeechEngine>
namespace TextEditTextToSpeech
{
class TextToSpeechKokoroEngine : public QTextToSpeechEngine
{
    Q_OBJECT
public:
    TextToSpeechKokoroEngine(const QVariantMap &parameters, QObject *parent);
    ~TextToSpeechKokoroEngine() override;
};
}
