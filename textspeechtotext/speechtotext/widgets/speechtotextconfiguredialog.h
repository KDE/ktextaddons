/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "speechtotext_private_export.h"
#include <QDialog>
namespace TextSpeechToText
{
class SpeechToTextConfigureWidget;
/**
 * @brief The SpeechToTextConfigureDialog class
 * @author Laurent Montel <montel@kde.org>
 */

class TEXTSPEECHTOTEXT_TESTS_EXPORT SpeechToTextConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SpeechToTextConfigureDialog(QWidget *parent = nullptr);
    ~SpeechToTextConfigureDialog() override;

private:
    void slotAccept();
    SpeechToTextConfigureWidget *const mSpeechToTextConfigureWidget;
};
}
