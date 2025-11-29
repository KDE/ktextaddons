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

    [[nodiscard]] QList<QLocale> availableLocales() const override;
    [[nodiscard]] QList<QVoice> availableVoices() const override;
    void say(const QString &text) override;
    void synthesize(const QString &text) override;
    void stop(QTextToSpeech::BoundaryHint boundaryHint) override;
    void pause(QTextToSpeech::BoundaryHint boundaryHint) override;
    void resume() override;
    [[nodiscard]] double rate() const override;
    [[nodiscard]] bool setRate(double rate) override;
    [[nodiscard]] double pitch() const override;
    [[nodiscard]] bool setPitch(double pitch) override;
    [[nodiscard]] QLocale locale() const override;
    [[nodiscard]] bool setLocale(const QLocale &locale) override;
    [[nodiscard]] double volume() const override;
    [[nodiscard]] bool setVolume(double volume) override;
    [[nodiscard]] QVoice voice() const override;
    [[nodiscard]] bool setVoice(const QVoice &voice) override;
    [[nodiscard]] QTextToSpeech::State state() const override;
    [[nodiscard]] QTextToSpeech::ErrorReason errorReason() const override;
    [[nodiscard]] QString errorString() const override;
};

}
