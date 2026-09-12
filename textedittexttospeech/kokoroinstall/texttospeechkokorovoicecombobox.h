/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kokoroinstalltexttospeech_export.h"
#include <QComboBox>

namespace TextEditTextToSpeech
{
class KOKOROINSTALLTEXTTOSPEECH_EXPORT TextToSpeechKokoroVoiceComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroVoiceComboBox(QWidget *parent = nullptr);
    ~TextToSpeechKokoroVoiceComboBox() override;

    [[nodiscard]] QString currentVoice() const;

private:
    void fill();
};

}
