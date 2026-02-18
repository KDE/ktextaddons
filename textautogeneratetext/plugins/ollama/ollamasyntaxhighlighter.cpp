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
    for (const Rule &rule : std::as_const(m_rules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatchView(text);
        while (matchIterator.hasNext()) {
            const QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

void OllamaSyntaxHighlighter::init()
{
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::red);
        testFormat.setFontWeight(QFont::Bold);
        const QRegularExpression regex(u"\\[WARNING\\]"_s);
        m_rules.append(Rule(regex, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::green);
        const QRegularExpression regex(u"HEAD"_s);
        m_rules.append(Rule(regex, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::red);
        const QRegularExpression regex(u"DELETE"_s);
        m_rules.append(Rule(regex, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::blue);
        const QRegularExpression regex(u"POST"_s);
        m_rules.append(Rule(regex, testFormat));
    }
    {
        QTextCharFormat testFormat;
        testFormat.setForeground(Qt::cyan);
        const QRegularExpression regex(u"GET"_s);
        m_rules.append(Rule(regex, testFormat));
    }
}
#include "moc_ollamasyntaxhighlighter.cpp"
