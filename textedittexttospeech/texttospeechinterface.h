/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textedittexttospeech_export.h"
#include <QObject>
#include <TextEditTextToSpeech/TextToSpeechWidget>
namespace TextEditTextToSpeech
{
class TextToSpeechInterfacePrivate;
/**
 * @brief The TextToSpeechInterface class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechInterface : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechInterface(TextToSpeechWidget *textToSpeechWidget, QObject *parent = nullptr);
    ~TextToSpeechInterface() override;

    [[nodiscard]] bool isReady() const;
    void say(const QString &text);
    [[nodiscard]] double volume() const;
    void setVolume(double value);
    void reloadSettings();

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void stateChanged(TextEditTextToSpeech::TextToSpeechWidget::State state);
    std::unique_ptr<TextToSpeechInterfacePrivate> const d;
};
}
