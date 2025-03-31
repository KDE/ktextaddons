/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistoryinfotest.h"
#include "core/textautogeneratehistoryinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateHistoryInfoTest)

TextAutoGenerateHistoryInfoTest::TextAutoGenerateHistoryInfoTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateHistoryInfoTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutoGenerateHistoryInfo info;
    QVERIFY(info.subject().isEmpty());
    QCOMPARE(info.dateTime(), -1);
}

#include "moc_textautogeneratehistoryinfotest.cpp"
