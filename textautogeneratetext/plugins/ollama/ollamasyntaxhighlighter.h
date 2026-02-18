/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QRegularExpression>
#include <QSyntaxHighlighter>

class OllamaSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit OllamaSyntaxHighlighter(QTextDocument *doc = nullptr);
    ~OllamaSyntaxHighlighter() override;
    void highlightBlock(const QString &text) override;

protected:
    class Rule
    {
    public:
        Rule() = default;
        Rule(const QRegularExpression &r, const QTextCharFormat &f)
            : pattern(r)
            , format(f)
        {
        }
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    void init();
    QList<Rule> m_rules;
};
