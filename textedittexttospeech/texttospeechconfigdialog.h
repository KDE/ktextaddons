/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textedittexttospeech_export.h"
#include <QDialog>
namespace TextEditTextToSpeech
{
class TextToSpeechConfigWidget;
/*!
 * \class TextEditTextToSpeech::TextToSpeechConfigDialog
 * \inmodule TextEditTextToSpeech
 * \inheaderfile TextEditTextToSpeech/TextToSpeechConfigDialog
 *
 * \brief The TextToSpeechConfigDialog class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEDITTEXTTOSPEECH_EXPORT TextToSpeechConfigDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextToSpeechConfigDialog(QWidget *parent = nullptr);
    /*!
     */
    ~TextToSpeechConfigDialog() override;

private:
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotAccepted();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void slotRestoreDefaults();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void readConfig();
    TEXTEDITTEXTTOSPEECH_NO_EXPORT void writeConfig();
    TextEditTextToSpeech::TextToSpeechConfigWidget *const mTextToSpeechConfigWidget;
};
}
