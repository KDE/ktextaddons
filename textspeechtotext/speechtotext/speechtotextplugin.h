/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] QString result() const;

    virtual void speechToText() = 0;

    [[nodiscard]] virtual int sampleRate() const = 0;

    [[nodiscard]] QString defaultLanguage() const;
    [[nodiscard]] virtual QIODevice *audioDevice() const = 0;

    void setDefaultLanguage(const QString &language);

    [[nodiscard]] virtual bool loadSettings() = 0;

    virtual void clear() = 0;

Q_SIGNALS:
    void speechToTextDone(const QString &result);

private:
    std::unique_ptr<SpeechToTextPluginPrivate> const d;
};
}
