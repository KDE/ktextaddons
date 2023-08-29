/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textedittexttospeech_export.h"
#include <QWidget>
class QComboBox;
class QPushButton;
namespace TextEditTextToSpeech
{
class TextToSpeechLanguageComboBox;
class AbstractTextToSpeechConfigInterface;
class TextToSpeechSliderWidget;
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextToSpeechConfigWidget(QWidget *parent = nullptr);
    ~TextToSpeechConfigWidget() override;

    void initializeSettings();

    void writeConfig();
    void readConfig();

    void setTextToSpeechConfigInterface(AbstractTextToSpeechConfigInterface *interface);
    void restoreDefaults();

Q_SIGNALS:
    void configChanged(bool state);

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotTestTextToSpeech();
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
    TextToSpeechSliderWidget *const mVolume;
    TextToSpeechSliderWidget *const mRate;
    TextToSpeechSliderWidget *const mPitch;
    TextToSpeechLanguageComboBox *const mLanguage;
    AbstractTextToSpeechConfigInterface *mAbstractTextToSpeechConfigInterface = nullptr;
    QComboBox *const mAvailableEngine;
    QComboBox *const mVoice;
    QPushButton *const mTestButton;
};
}
