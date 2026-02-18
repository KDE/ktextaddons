/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textutils_export.h"
#include <KSyntaxHighlighting/AbstractHighlighter>
class QTextStream;
namespace TextUtils
{
/*!
 * \brief The TextUtilsSyntaxHighlighter class
 * \author Laurent Montel <montel@kde.org>
 * \class TextUtils::TextUtilsSyntaxHighlighter
 * \inheaderfile TextUtils/TextUtilsSyntaxHighlighter
 * \inmodule TextUtils
 */
class TEXTUTILS_EXPORT TextUtilsSyntaxHighlighter : public KSyntaxHighlighting::AbstractHighlighter
{
public:
    /*!
     * \brief Constructor for TextUtilsSyntaxHighlighter
     * \param stream The text stream to write highlighted output to
     */
    explicit TextUtilsSyntaxHighlighter(QTextStream *stream);
    /*!
     * \brief Destructor for TextUtilsSyntaxHighlighter
     */
    ~TextUtilsSyntaxHighlighter() override = default;

    /*!
     * \brief Highlights a string of text
     * \param str The text to highlight
     * \param uuid The unique identifier for the text block
     * \param blockCodeIndex The index of the code block
     */
    void highlight(const QString &str, const QByteArray &uuid, int &blockCodeIndex);

    /*!
     * \brief Returns the href for the copy button
     * \return The href string
     */
    [[nodiscard]] static QString copyHref();

protected:
    /*!
     * \brief Applies formatting to a range of text
     * \param offset The offset in the current line
     * \param length The length of the text to format
     * \param format The format to apply
     */
    void applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) override;

private:
    QString mCurrentLine;
    QTextStream *const mStream;
};
}
