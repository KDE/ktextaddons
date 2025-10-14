/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessagesettingstest.h"
#include "core/textautogeneratesearchmessagesettings.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateSearchMessageSettingsTest)

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

#include "moc_textautogeneratesearchmessagesettingstest.cpp"
