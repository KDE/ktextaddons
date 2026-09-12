/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokorovoicecomboboxtest.h"
#include "texttospeechkokoroutils.h"
#include "texttospeechkokorovoicecombobox.h"
#include <QTest>
QTEST_MAIN(TextToSpeechKokoroVoiceComboBoxTest)
TextToSpeechKokoroVoiceComboBoxTest::TextToSpeechKokoroVoiceComboBoxTest(QObject *parent)
    : QObject{parent}
{
}

void TextToSpeechKokoroVoiceComboBoxTest::shouldHaveDefaultValues()
{
    TextEditTextToSpeech::TextToSpeechKokoroVoiceComboBox w;
    QCOMPARE(w.count(), TextEditTextToSpeech::TextToSpeechKokoroUtils::kokoroVoices().count());
}

void TextToSpeechKokoroVoiceComboBoxTest::shouldHaveIconAndToolTipForEachVoice()
{
    TextEditTextToSpeech::TextToSpeechKokoroVoiceComboBox w;
    for (int i = 0; i < w.count(); ++i) {
        QVERIFY(!w.itemIcon(i).isNull());
        QVERIFY(!w.itemData(i, Qt::ToolTipRole).toString().isEmpty());
    }
}

#include "moc_texttospeechkokorovoicecomboboxtest.cpp"
