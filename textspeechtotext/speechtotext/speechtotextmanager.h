/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
namespace TextSpeechToText
{
class SpeechToTextPlugin;
/**
 * @brief The SpeechToTextManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextManager : public QObject
{
    Q_OBJECT
public:
    enum State {
        Record,
        Stop,
        // Pause ?
    };
    explicit SpeechToTextManager(QObject *parent = nullptr);
    ~SpeechToTextManager() override;

    void switchEngine(const QString &engineName);

Q_SIGNALS:
    void textToSpeechDone(const QString &result);

private:
    class SpeechToTextPluginPrivate;
    std::unique_ptr<SpeechToTextPluginPrivate> const d;
};
}
