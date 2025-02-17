/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emoticontonecomboboxtest.h"
#include "emoticontonecombobox.h"
#include <QTest>
QTEST_MAIN(EmoticonToneComboBoxTest)
EmoticonToneComboBoxTest::EmoticonToneComboBoxTest(QObject *parent)
    : QObject{parent}
{
}

void EmoticonToneComboBoxTest::shouldHaveDefaultValues()
{
    TextEmoticonsWidgets::EmoticonToneComboBox w;
    // TODO
}

#include "moc_emoticontonecomboboxtest.cpp"
