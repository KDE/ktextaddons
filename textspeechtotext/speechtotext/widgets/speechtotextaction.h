/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QAction>
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextAction : public QAction
{
    Q_OBJECT
public:
    explicit SpeechToTextAction(QObject *parent = nullptr);
    ~SpeechToTextAction() override;
};
}
