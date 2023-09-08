/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QComboBox>
namespace TextSpeechToText
{
class SpeechToTextCombobox : public QComboBox
{
    Q_OBJECT
public:
    explicit SpeechToTextCombobox(QWidget *parent);
    ~SpeechToTextCombobox() override;
};
}
