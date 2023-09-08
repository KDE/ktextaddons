/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
namespace TextSpeechToText
{
class SpeechToTextConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SpeechToTextConfigureDialog(QWidget *parent = nullptr);
    ~SpeechToTextConfigureDialog() override;
};
}
