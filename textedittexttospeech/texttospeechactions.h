/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textedittexttospeech_export.h"
#include <QObject>
#include <TextEditTextToSpeech/TextToSpeechWidget>
class QAction;
namespace TextEditTextToSpeech
{
class TextToSpeechActionsPrivate;
/**
 * @brief The TextToSpeechActions class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechActions : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechActions(QObject *parent = nullptr);
    ~TextToSpeechActions() override;

    [[nodiscard]] QAction *stopAction() const;

    [[nodiscard]] QAction *playPauseAction() const;

    [[nodiscard]] TextToSpeechWidget::State state() const;

public Q_SLOTS:
    void setState(TextToSpeechWidget::State);
    void slotStop();

Q_SIGNALS:
    void stateChanged(TextEditTextToSpeech::TextToSpeechWidget::State state);

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotPlayPause();
    std::unique_ptr<TextToSpeechActionsPrivate> const d;
};
}
