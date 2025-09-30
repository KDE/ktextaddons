/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojitonecomboboxtest.h"
#include "emojitonecombobox.h"
#include <QTest>
QTEST_MAIN(EmojiToneComboBoxTest)
EmojiToneComboBoxTest::EmojiToneComboBoxTest(QObject *parent)
    : QObject{parent}
{
}

void EmojiToneComboBoxTest::shouldHaveDefaultValues()
{
    TextEmoticonsWidgets::EmojiToneComboBox w;
    // TODO
}

#include "moc_emojitonecomboboxtest.cpp"
