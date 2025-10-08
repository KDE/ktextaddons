/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <KSyntaxHighlighting/AbstractHighlighter>

class QTextStream;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextHighlighter : public KSyntaxHighlighting::AbstractHighlighter
{
public:
    explicit TextAutoGenerateTextHighlighter(QTextStream *stream);
    ~TextAutoGenerateTextHighlighter() override = default;

    void highlight(const QString &str);

    [[nodiscard]] static QString copyHref();

protected:
    void applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) override;

private:
    QString mCurrentLine;
    QTextStream *const mStream;
};
}
