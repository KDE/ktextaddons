/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatormenutest.h"
#include <QMenu>
#include <QStandardPaths>
#include <QTest>
#include <TextTranslator/TranslatorMenu>

QTEST_MAIN(TranslatorMenuTest)
TranslatorMenuTest::TranslatorMenuTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TranslatorMenuTest::shouldHaveDefaultValues()
{
    TextTranslator::TranslatorMenu w;
    QVERIFY(w.menu());
    QVERIFY(w.isEmpty());
    QVERIFY(!w.menu()->title().isEmpty());
}

#include "moc_translatormenutest.cpp"
