/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "speechtotext_private_export.h"
#include <QWidget>
class QComboBox;
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_TESTS_EXPORT SpeechToTextSelectDeviceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpeechToTextSelectDeviceWidget(QWidget *parent = nullptr);
    ~SpeechToTextSelectDeviceWidget() override;

    void loadSettings();
    void saveSettings();

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void initializeInput();
    QComboBox *const mDeviceComboBox;
};
}
