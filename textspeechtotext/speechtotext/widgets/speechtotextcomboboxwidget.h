/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "speechtotext_private_export.h"
#include <QWidget>
class QComboBox;
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_TESTS_EXPORT SpeechToTextComboBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpeechToTextComboBoxWidget(QWidget *parent);
    ~SpeechToTextComboBoxWidget() override;
    void fillEngine();

private:
    QComboBox *const mEngine;
};
}
