/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolupdatecomboboxtest.h"
#include "languagetool/languagetoolupdatecombobox.h"
#include <QTest>
QTEST_MAIN(LanguageToolUpdateComboBoxTest)

LanguageToolUpdateComboBoxTest::LanguageToolUpdateComboBoxTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolUpdateComboBoxTest::shouldHaveDefaultValues()
{
    TextGrammarCheck::LanguageToolUpdateComboBox w;
    QVERIFY(!w.languageToolCombobox());
    QVERIFY(!w.parentWidget());
}

#include "moc_languagetoolupdatecomboboxtest.cpp"
