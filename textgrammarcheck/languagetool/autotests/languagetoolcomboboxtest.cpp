/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolcomboboxtest.h"
#include "languagetool/languagetoolcombobox.h"
#include <QTest>
QTEST_MAIN(LanguageToolComboBoxTest)
LanguageToolComboBoxTest::LanguageToolComboBoxTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolComboBoxTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::LanguageToolComboBox w;
    QCOMPARE(w.count(), 30);
}

#include "moc_languagetoolcomboboxtest.cpp"
