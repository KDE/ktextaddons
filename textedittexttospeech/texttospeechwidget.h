/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textedittexttospeech_export.h"
#include "texttospeech.h"
#include <QWidget>
namespace TextEditTextToSpeech
{
class TextToSpeechInterface;
class TextToSpeechWidgetPrivate;
/**
 * @brief The TextToSpeechWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextToSpeechWidget(QWidget *parent = nullptr);
    ~TextToSpeechWidget() override;

    enum State {
        Stop = 0,
        Play,
        Pause,
    };
    Q_ENUM(State)

    [[nodiscard]] State state() const;
    void setState(TextEditTextToSpeech::TextToSpeechWidget::State state);

    void setTextToSpeechInterface(TextToSpeechInterface *interface);

    [[nodiscard]] bool isReady() const;

    void showWidget();

public Q_SLOTS:
    void say(const QString &text);

    void slotStateChanged(TextEditTextToSpeech::TextToSpeech::State state);

Q_SIGNALS:
    void stateChanged(TextEditTextToSpeech::TextToSpeechWidget::State state);
    void changeVisibility(bool state);

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotVolumeChanged(int value);
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotCloseTextToSpeechWidget();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotConfigure();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void applyVolume();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void hideWidget();
    std::unique_ptr<TextToSpeechWidgetPrivate> const d;
};
}
