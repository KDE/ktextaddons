/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
namespace TextSpeechToText
{
class SpeechToTextPlugin;
/*!
 * \class TextSpeechToText::SpeechToTextManager
 * \inheaderfile TextSpeechToText/SpeechToTextManager
 * \inmodule TextSpeechToText
 * \brief Central manager for speech-to-text operations.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextManager : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit SpeechToTextManager(QObject *parent = nullptr);
    /*!
     */
    ~SpeechToTextManager() override;

    /*!
     * \brief Loads the engine stored in the configuration.
     *
     * Falls back to the first available engine when no engine was configured yet
     * or when the configured one is gone. Call it again after the settings
     * changed so the new engine is picked up.
     */
    void loadEngine();

    /*!
     */
    void switchEngine(const QString &engineName);

    /*!
     */
    static SpeechToTextManager *self();

    /*!
     * \brief Starts capturing the microphone and feeding it to the current engine.
     *
     * Does nothing when no engine is loaded or when a recognition is already running.
     */
    void speechToText();

    /*!
     * \brief Stops the running recognition, if any.
     *
     * The engine flushes its pending result, so textToSpeechDone() may still be
     * emitted after this call.
     */
    void stop();

    /*!
     * \brief Returns true while the microphone is being captured.
     */
    [[nodiscard]] bool isRecording() const;

    /*!
     */
    [[nodiscard]] bool hasEngine() const;

    /*!
     * \brief Returns true when an engine is loaded and ready to transcribe.
     */
    [[nodiscard]] bool isReady() const;

Q_SIGNALS:
    /*!
     */
    void textToSpeechDone(const QString &result);

    /*!
     * \brief Emitted when the capture starts or stops.
     */
    void recordingChanged(bool recording);

private:
    enum class EngineStatus : uint8_t {
        NotLoadedYet,
        Ready,
        NoEngineAvailable,
        EngineNotFound,
        EngineNotUsable,
    };
    TEXTSPEECHTOTEXT_NO_EXPORT void warnAboutMissingPlugin() const;
    TEXTSPEECHTOTEXT_NO_EXPORT void slotEngineConfigureChanged();
    TEXTSPEECHTOTEXT_NO_EXPORT void deletePlugin();
    [[nodiscard]] TEXTSPEECHTOTEXT_NO_EXPORT bool initializeInput();
    class SpeechToTextPluginPrivate;
    std::unique_ptr<SpeechToTextPluginPrivate> const d;
};
}
