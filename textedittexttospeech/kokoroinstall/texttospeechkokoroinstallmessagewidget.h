/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kokoroinstalltexttospeech_export.h"
#include <KMessageWidget>

namespace TextEditTextToSpeech
{
class KOKOROINSTALLTEXTTOSPEECH_EXPORT TextToSpeechKokoroInstallMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroInstallMessageWidget(QWidget *parent = nullptr);
    ~TextToSpeechKokoroInstallMessageWidget() override;

Q_SIGNALS:
    void installPackages();
};

}
