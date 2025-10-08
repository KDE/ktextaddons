/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textutils_export.h"
#include <KSyntaxHighlighting/AbstractHighlighter>
class QTextStream;
namespace TextUtils
{
class TEXTUTILS_EXPORT TextUtilsSyntaxHighlighter : public KSyntaxHighlighting::AbstractHighlighter
{
public:
    explicit TextUtilsSyntaxHighlighter(QTextStream *stream);
    ~TextUtilsSyntaxHighlighter() override = default;

    void highlight(const QString &str, const QByteArray &uuid, int &blockCodeIndex);

    [[nodiscard]] static QString copyHref();

protected:
    void applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) override;

private:
    QString mCurrentLine;
    QTextStream *const mStream;
};
}
