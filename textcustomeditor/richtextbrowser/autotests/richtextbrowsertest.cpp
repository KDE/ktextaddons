/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "richtextbrowsertest.h"
#include "richtextbrowser/richtextbrowser.h"
#include <QTest>

QTEST_MAIN(RichTextBrowserTest)
RichTextBrowserTest::RichTextBrowserTest(QObject *parent)
    : QObject(parent)
{
}

RichTextBrowserTest::~RichTextBrowserTest() = default;

void RichTextBrowserTest::shouldHaveDefaultValue()
{
    TextCustomEditor::RichTextBrowser editor;
    QCOMPARE(editor.textToSpeechSupport(), true);
    QCOMPARE(editor.searchSupport(), true);
    QCOMPARE(editor.webShortcutSupport(), true);
}

void RichTextBrowserTest::shouldChangeSpellCheckValue()
{
    TextCustomEditor::RichTextBrowser editor;

    editor.setTextToSpeechSupport(false);
    QCOMPARE(editor.textToSpeechSupport(), false);

    editor.setSearchSupport(false);
    QCOMPARE(editor.searchSupport(), false);

    editor.setWebShortcutSupport(false);
    QCOMPARE(editor.webShortcutSupport(), false);

    editor.setTextToSpeechSupport(true);
    QCOMPARE(editor.textToSpeechSupport(), true);

    editor.setSearchSupport(true);
    QCOMPARE(editor.searchSupport(), true);

    editor.setWebShortcutSupport(true);
    QCOMPARE(editor.webShortcutSupport(), true);
}

#include "moc_richtextbrowsertest.cpp"
