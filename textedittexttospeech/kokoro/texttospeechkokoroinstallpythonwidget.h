/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textedittexttospeech_kokoro_private_export.h"
#include <QWidget>
class QPlainTextEdit;
namespace TextEditTextToSpeech
{
class KOKOROTEXTTOSPEECH_TESTS_EXPORT TextToSpeechKokoroInstallPythonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroInstallPythonWidget(QWidget *parent = nullptr);
    ~TextToSpeechKokoroInstallPythonWidget() override;

private:
    QPlainTextEdit *const mPlainTextEdit;
};
}
