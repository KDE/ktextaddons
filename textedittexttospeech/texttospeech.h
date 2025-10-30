/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textedittexttospeech_export.h"
#include <QObject>
#include <memory>

namespace TextEditTextToSpeech
{
class TextToSpeechPrivate;
/**
 * @brief The TextToSpeech class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeech : public QObject
{
    Q_OBJECT
public:
    static TextToSpeech *self();

    ~TextToSpeech() override;

    [[nodiscard]] bool isReady() const;

    enum State {
        Ready = 0,
        Speaking,
        Paused,
        BackendError,
        Synthesizing,
    };

    [[nodiscard]] double volume() const;
    [[nodiscard]] QVector<QLocale> availableLocales() const;
    [[nodiscard]] QStringList availableEngines() const;
    [[nodiscard]] QStringList availableVoices() const;

    [[nodiscard]] QLocale locale() const;

    void reloadSettings();
    [[nodiscard]] qsizetype enqueue(const QString &text);

public Q_SLOTS:
    void say(const QString &text);
    void stop();
    void pause();
    void resume();

    void setRate(double rate);
    void setPitch(double pitch);
    void setVolume(double volume);
    void setLocale(const QLocale &locale) const;

Q_SIGNALS:
    void stateChanged(TextToSpeech::State);
    void aboutToSynthesize(qsizetype previousId, qsizetype currentId);

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotStateChanged();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT explicit TextToSpeech(QObject *parent = nullptr);
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotAboutToSynthesize(qsizetype id);

    std::unique_ptr<TextToSpeechPrivate> const d;
};
}
