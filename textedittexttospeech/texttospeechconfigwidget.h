/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textedittexttospeech_export.h"
#include <QTextToSpeech>
#include <QWidget>
class QComboBox;
class QPushButton;
namespace TextEditTextToSpeech
{
class TextToSpeechLanguageComboBox;
class TextToSpeechConfigInterface;
class TextToSpeechSliderWidget;
class TextToSpeechVoiceComboBox;
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextToSpeechConfigWidget(QWidget *parent = nullptr);
    ~TextToSpeechConfigWidget() override;

    void initializeSettings();

    void writeConfig();
    void readConfig();

    void setTextToSpeechConfigInterface(TextToSpeechConfigInterface *interface);
    void restoreDefaults();

Q_SIGNALS:
    void configChanged(bool state);

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotTestTextToSpeech(bool checked);
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void valueChanged();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotLocalesAndVoices();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotUpdateSettings();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotEngineChanged();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotLanguageChanged();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void updateVoice();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void updateLocale();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void updateEngine();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void updateAvailableLocales();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void updateAvailableEngine();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void updateAvailableVoices();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotAvailableEngineChanged();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotTextChanged(QTextToSpeech::State state);
    TextToSpeechSliderWidget *const mVolume;
    TextToSpeechSliderWidget *const mRate;
    TextToSpeechSliderWidget *const mPitch;
    QComboBox *const mAvailableEngine;
    TextToSpeechLanguageComboBox *const mLanguage;
    TextToSpeechConfigInterface *mTextToSpeechConfigInterface = nullptr;
    TextToSpeechVoiceComboBox *const mVoice;
    QPushButton *const mTestButton;
};
}
