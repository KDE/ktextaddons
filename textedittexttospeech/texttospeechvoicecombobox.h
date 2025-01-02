/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textedittexttospeech_private_export.h"
#include <QComboBox>
#include <QVoice>
namespace TextEditTextToSpeech
{
class TEXTEDITTEXTTOSPEECH_TESTS_EXPORT TextToSpeechVoiceComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextToSpeechVoiceComboBox(QWidget *parent = nullptr);
    ~TextToSpeechVoiceComboBox() override;

    [[nodiscard]] QVoice currentVoice() const;
    void setCurrentVoice(const QVoice &voice);
    void updateVoices(const QVector<QVoice> &voices);
};
}
