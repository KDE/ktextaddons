/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
#include <memory>
namespace TextSpeechToText
{
class SpeechToTextPluginPrivate;
/*!
 * \class TextSpeechToText::SpeechToTextPlugin
 * \inheaderfile TextSpeechToText/SpeechToTextPlugin
 * \inmodule TextSpeechToText
 * \brief Interface for speech-to-text engine implementations.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextPlugin : public QObject
{
    Q_OBJECT
public:
    enum PluginStatus {
        Unknown = 0,
        NoMicrophoneFound,
        Waiting,
        Running,
        Paused,
        PermissionMissing,
    };
    Q_ENUM(PluginStatus)

    /*!
     */
    explicit SpeechToTextPlugin(QObject *parent = nullptr);
    /*!
     */
    ~SpeechToTextPlugin() override;

    /*!
     */
    [[nodiscard]] QString result() const;

    /*!
     */
    virtual void speechToText() = 0;

    /*!
     */
    [[nodiscard]] virtual int sampleRate() const = 0;

    /*!
     */
    [[nodiscard]] QString defaultLanguage() const;
    /*!
     */
    [[nodiscard]] virtual QIODevice *audioDevice() const = 0;

    /*!
     */
    void setDefaultLanguage(const QString &language);

    /*!
     */
    [[nodiscard]] virtual bool loadSettings() = 0;

    /*!
     */
    virtual void clear() = 0;

    /*!
     * \brief Stops the running recognition and flushes the pending result.
     *
     * Called by SpeechToTextManager once the audio capture has been stopped, so
     * that the engine can emit what it recognized from the audio buffered so far.
     * The default implementation does nothing.
     */
    virtual void stop();

Q_SIGNALS:
    /*!
     */
    void speechToTextDone(const QString &result);

private:
    std::unique_ptr<SpeechToTextPluginPrivate> const d;
};
}
