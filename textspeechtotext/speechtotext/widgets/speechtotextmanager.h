/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
namespace TextSpeechToText
{
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
};
}
