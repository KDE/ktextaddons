/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>
#include <QSyntaxHighlighter>

class OllamaSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit OllamaSyntaxHighlighter(QTextDocument *doc = nullptr);
    ~OllamaSyntaxHighlighter() override;
    void highlightBlock(const QString &text) override;

private:
    class Rule
    {
    public:
        Rule() = default;
        Rule(const QString &r, const QTextCharFormat &f)
            : pattern(r)
            , format(f)
        {
        }
        QString pattern;
        QTextCharFormat format;
    };
    void init();
    QList<Rule> mRules;
};
