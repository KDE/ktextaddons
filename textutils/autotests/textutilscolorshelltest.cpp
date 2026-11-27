/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textutilscolorshelltest.h"

#include "colorshell/textutilscolorshell.h"
#include <QTest>

using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextUtilsColorShellTest)
TextUtilsColorShellTest::TextUtilsColorShellTest(QObject *parent)
    : QObject{parent}
{
}

void TextUtilsColorShellTest::initTestCase()
{
    // useAnsiFormatting() caches its result: NO_COLOR must be set before the first call
    qputenv("NO_COLOR", "1");
}

void TextUtilsColorShellTest::shouldNotUseAnsiFormattingWithNoColor()
{
    QVERIFY(!TextUtils::TextUtilsColorShell::useAnsiFormatting());
}

void TextUtilsColorShellTest::shouldReturnPlainText()
{
    const QString text(u"foo"_s);
    QCOMPARE(TextUtils::TextUtilsColorShell::bold(text), text);
    QCOMPARE(TextUtils::TextUtilsColorShell::dim(text), text);
    QCOMPARE(TextUtils::TextUtilsColorShell::cyan(text), text);
    QCOMPARE(TextUtils::TextUtilsColorShell::ansi(text, "\x1b[1m"_L1, "\x1b[22m"_L1), text);
}

#include "moc_textutilscolorshelltest.cpp"
