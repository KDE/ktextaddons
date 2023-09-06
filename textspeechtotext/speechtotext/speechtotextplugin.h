/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QObject>
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextPlugin : public QObject
{
    Q_OBJECT
public:
    explicit SpeechToTextPlugin(QObject *parent = nullptr);
    ~SpeechToTextPlugin() override;
};
}
