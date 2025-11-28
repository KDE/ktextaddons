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

    // QTextToSpeechEngine interface
public:
    QList<QLocale> availableLocales() const override;
    QList<QVoice> availableVoices() const override;
    void say(const QString &text) override;
    void synthesize(const QString &text) override;
    void stop(QTextToSpeech::BoundaryHint boundaryHint) override;
    void pause(QTextToSpeech::BoundaryHint boundaryHint) override;
    void resume() override;
    double rate() const override;
    bool setRate(double rate) override;
    double pitch() const override;
    bool setPitch(double pitch) override;
    QLocale locale() const override;
    bool setLocale(const QLocale &locale) override;
    double volume() const override;
    bool setVolume(double volume) override;
    QVoice voice() const override;
    bool setVoice(const QVoice &voice) override;
    QTextToSpeech::State state() const override;
    QTextToSpeech::ErrorReason errorReason() const override;
    QString errorString() const override;
};

}
