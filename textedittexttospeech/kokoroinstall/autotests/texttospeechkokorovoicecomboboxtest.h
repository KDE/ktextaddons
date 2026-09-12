/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextToSpeechKokoroVoiceComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroVoiceComboBoxTest(QObject *parent = nullptr);
    ~TextToSpeechKokoroVoiceComboBoxTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldHaveIconAndToolTipForEachVoice();
    void shouldCheckEachVoice();
    void shouldSelectVoices();
};
