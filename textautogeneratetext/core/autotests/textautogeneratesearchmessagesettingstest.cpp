/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessagesettingstest.h"
#include "core/textautogeneratesearchmessagesettings.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateSearchMessageSettingsTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSearchMessageSettingsTest::TextAutoGenerateSearchMessageSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchMessageSettingsTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchMessageSettings w(nullptr);
    QCOMPARE(w.currentSearchIndex(), -1);
    QCOMPARE(w.numberOfSearchReference(), -1);
    QVERIFY(w.currentMessageIdentifier().isEmpty());
}

void TextAutoGenerateSearchMessageSettingsTest::shouldClear()
{
    TextAutoGenerateText::TextAutoGenerateSearchMessageSettings w(nullptr);
    const QByteArray ba = "foo"_ba;
    w.setCurrentMessageIdentifier(ba);
    QCOMPARE(w.currentMessageIdentifier(), ba);

    const int nbSearch = 15;
    w.setNumberOfSearchReference(nbSearch);
    QCOMPARE(w.numberOfSearchReference(), nbSearch);

    const int currentSearchIndex = 45;
    w.setCurrentSearchIndex(currentSearchIndex);
    QCOMPARE(w.currentSearchIndex(), currentSearchIndex);

    w.clear();
    QCOMPARE(w.currentSearchIndex(), -1);
    QCOMPARE(w.numberOfSearchReference(), -1);
    QVERIFY(w.currentMessageIdentifier().isEmpty());
}

#include "moc_textautogeneratesearchmessagesettingstest.cpp"
