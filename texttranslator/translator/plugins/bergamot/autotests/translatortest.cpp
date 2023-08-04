/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatortest.h"
#include "translator.h"
#include <QTest>
QTEST_GUILESS_MAIN(TranslatorTest)
TranslatorTest::TranslatorTest(QObject *parent)
    : QObject{parent}
{
}

void TranslatorTest::shouldHaveDefaultValues()
{
    Translator w;
    QVERIFY(w.shortName().isEmpty());
    QVERIFY(w.modelName().isEmpty());
    QVERIFY(w.source().isEmpty());
    QVERIFY(w.checkSum().isEmpty());
    QVERIFY(w.target().isEmpty());
    QVERIFY(w.url().isEmpty());
    QVERIFY(w.repository().isEmpty());
    QVERIFY(w.type().isEmpty());
    QCOMPARE(w.version(), -1);
    QCOMPARE(w.api(), -1);
}

#include "moc_translatortest.cpp"
