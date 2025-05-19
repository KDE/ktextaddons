/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessageutilstest.h"
#include "core/textautogeneratesearchmessageutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(TextAutoGenerateSearchMessageUtilsTest)
TextAutoGenerateSearchMessageUtilsTest::TextAutoGenerateSearchMessageUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchMessageUtilsTest::shouldGenerateGoToMessageLink()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateSearchMessageUtils::generateGoToMessageLink(QStringLiteral("bla"), QStringLiteral("messageID")),
             QStringLiteral("storage://bla:messageID"));
    // TODO
}

#include "moc_textautogeneratesearchmessageutilstest.cpp"
