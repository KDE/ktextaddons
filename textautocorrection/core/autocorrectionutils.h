/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautocorrectioncore_export.h"
#include <QChar>
class QDebug;
namespace TextAutoCorrectionCore
{
namespace AutoCorrectionUtils
{
/*!
 * \class TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes
 * \inmodule TextAutoCorrectionCore
 *
 * \brief Represents opening and closing typographic quote characters.
 */
struct TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes {
    QChar begin; /*!< The opening quote character */
    QChar end; /*!< The closing quote character */
    /*!
     * \brief Converts the quotes to a string representation
     * \return A string containing the begin and end characters
     */
    [[nodiscard]] QString toString() const;
    /*!
     * \brief Checks if the quotes are empty
     * \return true if both begin and end characters are null
     */
    [[nodiscard]] bool isEmpty() const;
    /*!
     * \brief Creates TypographicQuotes from a string representation
     * \param str The string containing two quote characters
     * \return The TypographicQuotes parsed from the string
     */
    [[nodiscard]] static TypographicQuotes fromString(const QString &str);
};

/*!
 * \brief Returns the default single quote characters
 * \return The default typographic single quotes for the locale
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes typographicDefaultSingleQuotes();
/*!
 * \brief Returns the default double quote characters
 * \return The default typographic double quotes for the locale
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes typographicDefaultDoubleQuotes();
/*!
 * \brief Returns the default French quote characters
 * \return The default typographic French quotes
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT TypographicQuotes typographicDefaultFrenchQuotes();
/*!
 * \brief Returns the LibreOffice autocorrection file name for a language
 * \param lang The language code
 * \return The file name for the language
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreofficeFile(const QString &lang);
/*!
 * \brief Returns the LibreOffice autocorrection path
 * \return A list of autocorrection paths
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList libreOfficeAutoCorrectionPath();
/*!
 * \brief Searches for available LibreOffice autocorrection files
 * \return A list of available autocorrection file paths
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList searchAutoCorrectLibreOfficeFiles();
/*!
 * \brief Converts LibreOffice language names to standard language strings
 * \param langs The list of LibreOffice language names
 * \return A list of converted language strings
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList autoCorrectLibreOfficeLanguageToString(const QStringList &langs);
/*!
 * \brief Returns the writable local LibreOffice autocorrection path
 * \return The writable local autocorrection path
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreOfficeWritableLocalAutoCorrectionPath();
/*!
 * \brief Finds an autocorrection file for the specified language
 * \param lang The language code
 * \param customSystemPath The custom system path to search
 * \param customWritablePath The custom writable path to search
 * \return The path to the autocorrection file, or empty string if not found
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString containsAutoCorrectionFile(const QString &lang,
                                                                               const QString &customSystemPath,
                                                                               const QString &customWritablePath);
/*!
 * \brief Returns the LibreOffice system path for autocorrection files
 * \return The system path
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreOfficeSystemPath();
/*!
 * \brief Returns the LibreOffice local path for autocorrection files
 * \return The local path
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QString libreOfficeLocalPath();
/*!
 * \brief Extracts words from a sentence
 * \param string The sentence to parse
 * \return A list of words in the sentence
 */
[[nodiscard]] TEXTAUTOCORRECTIONCORE_EXPORT QStringList wordsFromSentence(const QString &string);
};
}
/*!
 * \brief Outputs TypographicQuotes to a debug stream
 * \param d The debug stream
 * \param t The TypographicQuotes to output
 * \return The debug stream
 */
TEXTAUTOCORRECTIONCORE_EXPORT QDebug operator<<(QDebug d, TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes t);
