/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textedittexttospeech_export.h"
#include <QObject>
#include <QVoice>

class QTextToSpeech;
namespace TextEditTextToSpeech
{
/**
 * @brief The TextToSpeechConfigInterface class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechConfigInterface : public QObject
{
    Q_OBJECT
public:
    struct EngineSettings {
        int rate = 0;
        int pitch = 0;
        int volume = 0;
        QVoice voice;
        QString localeName;
    };
    explicit TextToSpeechConfigInterface(QObject *parent = nullptr);
    ~TextToSpeechConfigInterface() override;

    [[nodiscard]] QVector<QLocale> availableLocales() const;
    [[nodiscard]] QLocale locale() const;

    [[nodiscard]] QStringList availableEngines() const;
    [[nodiscard]] QVector<QVoice> availableVoices() const;
    void setEngine(const QString &engineName);
    void testEngine(const EngineSettings &engineSettings);
    QTextToSpeech *mTextToSpeech = nullptr;
};
}
TEXTEDITTEXTTOSPEECH_EXPORT QDebug operator<<(QDebug d, const TextEditTextToSpeech::TextToSpeechConfigInterface::EngineSettings &t);
