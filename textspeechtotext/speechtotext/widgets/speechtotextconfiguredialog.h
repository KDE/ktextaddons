/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textspeechtotext_export.h"
#include <QDialog>
namespace TextSpeechToText
{
class SpeechToTextConfigureWidget;
/**
 * @brief The SpeechToTextConfigureDialog class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTSPEECHTOTEXT_EXPORT SpeechToTextConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \brief SpeechToTextConfigureDialog
     * \param parent
     */
    explicit SpeechToTextConfigureDialog(QWidget *parent = nullptr);
    /*!
     * \brief ~SpeechToTextConfigureDialog
     */
    ~SpeechToTextConfigureDialog() override;

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void slotAccept();
    SpeechToTextConfigureWidget *const mSpeechToTextConfigureWidget;
};
}
