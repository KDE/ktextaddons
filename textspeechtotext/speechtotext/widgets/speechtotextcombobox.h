/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "speechtotext/speechtotext_private_export.h"
#include <QComboBox>
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_TESTS_EXPORT SpeechToTextComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SpeechToTextComboBox(QWidget *parent);
    ~SpeechToTextComboBox() override;
};
}
