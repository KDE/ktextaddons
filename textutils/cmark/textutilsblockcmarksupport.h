/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QString>
namespace TextUtils
{
/*!
 * \brief The TextUtilsBlockCMarkSupport class
 * \author Laurent Montel <montel@kde.org>
 * \class TextUtils::TextUtilsBlockCMarkSupport
 * \inheaderfile TextUtils/TextUtilsBlockCMarkSupport
 * \inmodule TextUtils
 */
class TEXTUTILS_EXPORT TextUtilsBlockCMarkSupport
{
public:
    /*!
     * \brief Constructor for TextUtilsBlockCMarkSupport
     */
    TextUtilsBlockCMarkSupport();
    /*!
     * \brief Virtual destructor for TextUtilsBlockCMarkSupport
     */
    virtual ~TextUtilsBlockCMarkSupport();
    /*!
     * \brief Converts message text with markdown support
     * \param str The text to convert
     * \param uuid The unique identifier for the message
     * \param searchText The text to search for highlighting
     * \param numberOfTextSearched The number of text matches found
     * \param hightLightStringIndex The index of the highlight
     * \return The converted text with markdown formatting
     */
    [[nodiscard]] QString
    convertMessageText(const QString &str, const QByteArray &uuid, const QString &searchText, int &numberOfTextSearched, int hightLightStringIndex);

    /*!
     * \brief Finds a non-escaped occurrence of a region marker
     * \param str The string to search in
     * \param regionMarker The marker to find
     * \param startFrom The position to start searching from
     * \return The position of the marker, or -1 if not found
     */
    [[nodiscard]] static int findNonEscaped(const QString &str, const QString &regionMarker, int startFrom);
    /*!
     * \brief Checks if a character at a position is escaped
     * \param str The string containing the character
     * \param pos The position of the character
     * \return True if the character is escaped, false otherwise
     */
    [[nodiscard]] static bool isEscaped(const QString &str, int pos);

    /*!
     * \brief Finds the next newline or end of line
     * \param str The string to search in
     * \param regionMarker The marker to look for
     * \param startFrom The position to start searching from
     * \return The position of the newline or end of line
     */
    [[nodiscard]] static int findNewLineOrEndLine(const QString &str, const QString &regionMarker, int startFrom);

    /*!
     * \brief Converts text with URLs to markup
     * \param str The text containing URLs
     * \return The text with URLs converted to markup
     */
    [[nodiscard]] static QString convertTextWithUrl(const QString &str);

    /*!
     * \brief Converts markdown with CommonMark format to rich text
     * \param markDown The markdown text to convert
     * \return The rich text representation
     */
    [[nodiscard]] static QString markdownToRichTextCMark(const QString &markDown);

protected:
    /*!
     */
    [[nodiscard]] virtual QString addHighlighter(const QString &str,
                                                 const QString &language,
                                                 const QString &searchText,
                                                 const QByteArray &uuid,
                                                 int &blockCodeIndex,
                                                 int &numberOfTextSearched,
                                                 int hightLightStringIndex) = 0;
};
}
