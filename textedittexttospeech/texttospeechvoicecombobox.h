/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT QVoice currentVoice() const;
    void updateVoices(const QVector<QVoice> &voices);
};
}
#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
Q_DECLARE_METATYPE(QVoice)
#endif