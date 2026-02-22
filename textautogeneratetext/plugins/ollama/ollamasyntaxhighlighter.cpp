/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamasyntaxhighlighter.h"

using namespace Qt::Literals::StringLiterals;

OllamaSyntaxHighlighter::OllamaSyntaxHighlighter(QTextDocument *doc)
    : QSyntaxHighlighter{doc}
{
    init();
}

OllamaSyntaxHighlighter::~OllamaSyntaxHighlighter() = default;

void OllamaSyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const Rule &rule : std::as_const(mRules)) {
        const QString searchText = rule.pattern;
        int index = 0;
        while (index >= 0) {
            index = text.indexOf(searchText, index);
            if (index < 0) {
                break;
            }
            setFormat(index, searchText.length(), rule.format);
            index += searchText.length();
        }
    }
}

void OllamaSyntaxHighlighter::init()
{
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::red);
        testFormat.setFontWeight(QFont::Bold);
        mRules.append(Rule(u"[WARNING]"_s, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::green);
        mRules.append(Rule(u" HEAD "_s, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::red);
        mRules.append(Rule(u" DELETE "_s, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::blue);
        mRules.append(Rule(u" POST "_s, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::cyan);
        mRules.append(Rule(u" GET "_s, testFormat));
    }
}
#include "moc_ollamasyntaxhighlighter.cpp"
