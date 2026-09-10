/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textedittexttospeech_kokoro_private_export.h"
#include <QDialog>
#include <QStringList>
class QPushButton;
namespace TextEditTextToSpeech
{
class TextToSpeechKokoroInstallPythonWidget;
class KOKOROTEXTTOSPEECH_TESTS_EXPORT TextToSpeechKokoroInstallPythonDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroInstallPythonDialog(QWidget *parent = nullptr);
    ~TextToSpeechKokoroInstallPythonDialog() override;

    void setModules(const QStringList &modules);
    void startInstall();

private:
    TextToSpeechKokoroInstallPythonWidget *const mKokoroInstallPythonWidget;
    QPushButton *const mCloseButton;
};
}
