/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchmessageutilstest.h"
using namespace Qt::Literals::StringLiterals;

#include "core/textautogeneratesearchmessageutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(TextAutoGenerateSearchMessageUtilsTest)
TextAutoGenerateSearchMessageUtilsTest::TextAutoGenerateSearchMessageUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchMessageUtilsTest::shouldGenerateGoToMessageLink()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateSearchMessageUtils::generateGoToMessageLink(u"bla"_s, u"messageID"_s), u"storage://bla:messageID"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateSearchMessageUtils::generateGoToMessageLink(u"foo"_s, u"msg1"_s), u"storage://foo:msg1"_s);
}

#include "moc_textautogeneratesearchmessageutilstest.cpp"
