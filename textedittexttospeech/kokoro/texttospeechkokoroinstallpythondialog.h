/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "kokorotexttospeech_export.h"
#include <QDialog>
namespace TextEditTextToSpeech
{
class KOKOROTEXTTOSPEECH_EXPORT TextToSpeechKokoroInstallPythonDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroInstallPythonDialog(QWidget *parent = nullptr);
    ~TextToSpeechKokoroInstallPythonDialog() override;
};
}
