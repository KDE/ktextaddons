/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokorovoicecomboboxtest.h"
#include "texttospeechkokoroutils.h"
#include "texttospeechkokorovoicecombobox.h"
#include <QSignalSpy>
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
    QVERIFY(w.selectedVoices().isEmpty());
}

void TextToSpeechKokoroVoiceComboBoxTest::shouldHaveIconAndToolTipForEachVoice()
{
    TextEditTextToSpeech::TextToSpeechKokoroVoiceComboBox w;
    for (int i = 0; i < w.count(); ++i) {
        QVERIFY(!w.itemIcon(i).isNull());
        QVERIFY(!w.itemData(i, Qt::ToolTipRole).toString().isEmpty());
    }
}

void TextToSpeechKokoroVoiceComboBoxTest::shouldCheckEachVoice()
{
    TextEditTextToSpeech::TextToSpeechKokoroVoiceComboBox w;
    for (int i = 0; i < w.count(); ++i) {
        QCOMPARE(w.itemData(i, Qt::CheckStateRole).value<Qt::CheckState>(), Qt::Unchecked);
        QVERIFY(!w.itemData(i).toString().isEmpty());
    }
}

void TextToSpeechKokoroVoiceComboBoxTest::shouldSelectVoices()
{
    TextEditTextToSpeech::TextToSpeechKokoroVoiceComboBox w;
    const QList<TextEditTextToSpeech::TextToSpeechKokoroUtils::KokoroVoice> voices = TextEditTextToSpeech::TextToSpeechKokoroUtils::kokoroVoices();
    QVERIFY(voices.count() > 1);
    const QStringList identifiers{voices.at(0).identifier, voices.at(1).identifier};

    QSignalSpy spy(&w, &TextEditTextToSpeech::TextToSpeechKokoroVoiceComboBox::selectedVoicesChanged);
    w.setSelectedVoices(identifiers);
    // One signal for the whole selection, not one per item.
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toStringList(), identifiers);
    QCOMPARE(w.selectedVoices(), identifiers);

    w.setSelectedVoices({});
    QCOMPARE(spy.count(), 2);
    QVERIFY(w.selectedVoices().isEmpty());
}

#include "moc_texttospeechkokorovoicecomboboxtest.cpp"
