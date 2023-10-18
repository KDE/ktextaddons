/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
#include <memory>
namespace TextSpeechToText
{
/**
 * @brief The SpeechToTextPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class SpeechToTextPluginPrivate;
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

    explicit SpeechToTextPlugin(QObject *parent = nullptr);
    ~SpeechToTextPlugin() override;

    Q_REQUIRED_RESULT QString result() const;

    virtual void speechToText() = 0;

    Q_REQUIRED_RESULT virtual int sampleRate() const = 0;

    Q_REQUIRED_RESULT virtual QString defaultLanguage() const = 0;
    Q_REQUIRED_RESULT virtual QIODevice *audioDevice() const = 0;

Q_SIGNALS:
    void speechToTextDone(const QString &result);

private:
    std::unique_ptr<SpeechToTextPluginPrivate> const d;
};
}
