/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "speechtotext_private_export.h"
#include <QWidget>
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_TESTS_EXPORT SpeechToTextLanguageComboBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpeechToTextLanguageComboBoxWidget(QWidget *parent = nullptr);
    ~SpeechToTextLanguageComboBoxWidget() override;
};
}
