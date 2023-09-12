/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QWidget>
namespace TextSpeechToText
{
class SpeechToTextComboBox;
/**
 * @brief The SpeechToTextConfigureWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpeechToTextConfigureWidget(QWidget *parent = nullptr);
    ~SpeechToTextConfigureWidget() override;
    void loadSettings();
    void saveSettings();

private:
    SpeechToTextComboBox *const mSpeechToTextComboBox;
};
}
