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
    explicit SpeechToTextPlugin(QObject *parent = nullptr);
    ~SpeechToTextPlugin() override;

    Q_REQUIRED_RESULT QString result() const;

    virtual void speechToText() = 0;

Q_SIGNALS:
    void speechToTextDone();

private:
    std::unique_ptr<SpeechToTextPluginPrivate> const d;
};
}
