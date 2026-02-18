/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autocorrectionutils.h"
#include "textautocorrectioncore_export.h"
class QDebug;
#include <QSet>
namespace TextAutoCorrectionCore
{
class AutoCorrectionSettingsPrivate;
/*!
 * \brief The AutoCorrectionSettings class
 * \author Laurent Montel <montel@kde.org>
 * \class TextAutoCorrectionCore::AutoCorrectionSettings
 * \inheaderfile TextAutoCorrectionCore/AutoCorrectionSettings
 * \inmodule TextAutoCorrectionCore
 */
class TEXTAUTOCORRECTIONCORE_EXPORT AutoCorrectionSettings
{
public:
    /*!
     * \brief Constructs an AutoCorrectionSettings instance
     */
    AutoCorrectionSettings();
    /*!
     * \brief Destroys the AutoCorrectionSettings instance
     */
    ~AutoCorrectionSettings();

    /*!
     * \brief Checks if automatic correction is enabled
     * \return true if autocorrection is enabled
     */
    [[nodiscard]] bool isEnabledAutoCorrection() const;
    /*!
     * \brief Checks if first character of sentences should be uppercase
     * \return true if uppercase first character is enabled
     */
    [[nodiscard]] bool isUppercaseFirstCharOfSentence() const;
    /*!
     * \brief Checks if fixing two consecutive uppercase characters is enabled
     * \return true if fix two uppercase chars is enabled
     */
    [[nodiscard]] bool isFixTwoUppercaseChars() const;
    /*!
     * \brief Checks if single spaces mode is enabled
     * \return true if single spaces is enabled
     */
    [[nodiscard]] bool isSingleSpaces() const;
    /*!
     * \brief Checks if automatic fraction conversion is enabled
     * \return true if auto fractions is enabled
     */
    [[nodiscard]] bool isAutoFractions() const;
    /*!
     * \brief Checks if capitalizing weekday names is enabled
     * \return true if capitalize weekdays is enabled
     */
    [[nodiscard]] bool isCapitalizeWeekDays() const;
    /*!
     * \brief Checks if replacing double quotes is enabled
     * \return true if replace double quotes is enabled
     */
    [[nodiscard]] bool isReplaceDoubleQuotes() const;
    /*!
     * \brief Checks if replacing single quotes is enabled
     * \return true if replace single quotes is enabled
     */
    [[nodiscard]] bool isReplaceSingleQuotes() const;
    /*!
     * \brief Checks if advanced autocorrection is enabled
     * \return true if advanced autocorrect is enabled
     */
    [[nodiscard]] bool isAdvancedAutocorrect() const;
    /*!
     * \brief Checks if automatic URL formatting is enabled
     * \return true if auto format URL is enabled
     */
    [[nodiscard]] bool isAutoFormatUrl() const;
    /*!
     * \brief Checks if automatic bold and underline formatting is enabled
     * \return true if auto bold underline is enabled
     */
    [[nodiscard]] bool isAutoBoldUnderline() const;
    /*!
     * \brief Checks if superscript conversion is enabled
     * \return true if superscript is enabled
     */
    [[nodiscard]] bool isSuperScript() const;

    /*!
     * \brief Checks if adding non-breaking spaces is enabled
     * \return true if add non-breaking space is enabled
     */
    [[nodiscard]] bool isAddNonBreakingSpace() const;
    /*!
     * \brief Checks if replacing double quotes with French quotes is enabled
     * \return true if replace double quotes by French quotes is enabled
     */
    [[nodiscard]] bool isReplaceDoubleQuotesByFrenchQuotes() const;

    /*!
     * \brief Returns the typographic single quote characters
     * \return The typographic single quotes
     */
    [[nodiscard]] TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes typographicSingleQuotes() const;
    /*!
     * \brief Returns the typographic double quote characters
     * \return The typographic double quotes
     */
    [[nodiscard]] TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes typographicDoubleQuotes() const;
    /*!
     * \brief Sets the typographic single quote characters
     * \param singleQuote The single quote characters to use
     */
    void setTypographicSingleQuotes(TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes singleQuote);
    /*!
     * \brief Sets the typographic double quote characters
     * \param doubleQuote The double quote characters to use
     */
    void setTypographicDoubleQuotes(TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes doubleQuote);

    /*!
     * \brief Sets whether automatic URL formatting is enabled
     * \param b true to enable auto format URL
     */
    void setAutoFormatUrl(bool b);
    /*!
     * \brief Sets whether automatic bold and underline formatting is enabled
     * \param b true to enable auto bold underline
     */
    void setAutoBoldUnderline(bool b);
    /*!
     * \brief Sets whether superscript conversion is enabled
     * \param b true to enable superscript
     */
    void setSuperScript(bool b);
    /*!
     * \brief Sets whether adding non-breaking spaces is enabled
     * \param b true to enable add non-breaking space
     */
    void setAddNonBreakingSpace(bool b);
    /*!
     * \brief Sets whether capitalizing weekday names is enabled
     * \param b true to enable capitalize weekdays
     */
    void setCapitalizeWeekDays(bool b);
    /*!
     * \brief Sets whether replacing double quotes is enabled
     * \param b true to enable replace double quotes
     */
    void setReplaceDoubleQuotes(bool b);
    /*!
     * \brief Sets whether replacing single quotes is enabled
     * \param b true to enable replace single quotes
     */
    void setReplaceSingleQuotes(bool b);
    /*!
     * \brief Sets whether advanced autocorrection is enabled
     * \param b true to enable advanced autocorrect
     */
    void setAdvancedAutocorrect(bool b);
    /*!
     * \brief Sets whether automatic correction is enabled
     * \param b true to enable autocorrection
     */
    void setEnabledAutoCorrection(bool b);
    /*!
     * \brief Sets whether replacing double quotes with French quotes is enabled
     * \param b true to enable replace double quotes by French quotes
     */
    void setReplaceDoubleQuotesByFrenchQuotes(bool b);

    /*!
     * \brief Reads the configuration from settings
     */
    void readConfig();

    /*!
     * \brief Writes the configuration to settings
     */
    void writeConfig();

    /*!
     * \brief Sets whether automatic fraction conversion is enabled
     * \param newAutoFractions true to enable auto fractions
     */
    void setAutoFractions(bool newAutoFractions);

    /*!
     * \brief Sets whether single spaces mode is enabled
     * \param newSingleSpaces true to enable single spaces
     */
    void setSingleSpaces(bool newSingleSpaces);

    /*!
     * \brief Sets whether fixing two consecutive uppercase characters is enabled
     * \param newFixTwoUppercaseChars true to enable fix two uppercase chars
     */
    void setFixTwoUppercaseChars(bool newFixTwoUppercaseChars);

    /*!
     * \brief Sets whether first character of sentences should be uppercase
     * \param newUppercaseFirstCharOfSentence true to enable uppercase first char of sentence
     */
    void setUppercaseFirstCharOfSentence(bool newUppercaseFirstCharOfSentence);

    /*!
     * \brief Sets the list of uppercase exceptions
     * \param exceptions The set of words that should not have their first character uppercased
     */
    void setUpperCaseExceptions(const QSet<QString> &exceptions);
    /*!
     * \brief Sets the list of two-upper-letter exceptions
     * \param exceptions The set of words that should not be changed from two uppercase letters
     */
    void setTwoUpperLetterExceptions(const QSet<QString> &exceptions);
    /*!
     * \brief Returns the list of uppercase exceptions
     * \return The set of words that should not have their first character uppercased
     */
    [[nodiscard]] const QSet<QString> &upperCaseExceptions() const;
    /*!
     * \brief Returns the list of two-upper-letter exceptions
     * \return The set of words that should not be changed from two uppercase letters
     */
    [[nodiscard]] QSet<QString> twoUpperLetterExceptions() const;

    /*!
     * \brief Sets the language for autocorrection
     * \param lang The language code
     * \param forceGlobal true to force use of global settings
     */
    void setLanguage(const QString &lang, bool forceGlobal = false);
    /*!
     * \brief Returns the current language setting
     * \return The language code
     */
    [[nodiscard]] QString language() const;

    /*!
     * \brief Checks if the current language is French
     * \return true if the language is French
     */
    [[nodiscard]] bool isFrenchLanguage() const;
    /*!
     * \brief Sets the autocorrection entries
     * \param entries A hash mapping incorrect text to correct replacements
     */
    void setAutocorrectEntries(const QHash<QString, QString> &entries);

    /*!
     * \brief Returns the autocorrection entries
     * \return A hash of autocorrection replacements
     */
    [[nodiscard]] QHash<QString, QString> autocorrectEntries() const;
    /*!
     * \brief Adds an autocorrection entry
     * \param currentWord The word to be replaced
     * \param replaceWord The replacement word
     * \return true if the entry was added successfully
     */
    [[nodiscard]] bool addAutoCorrect(const QString &currentWord, const QString &replaceWord);

    /*!
     * \brief Returns the non-breaking space character
     * \return The non-breaking space character
     */
    [[nodiscard]] QChar nonBreakingSpace() const;
    /*!
     * \brief Sets the non-breaking space character
     * \param newNonBreakingSpace The non-breaking space character to use
     */
    void setNonBreakingSpace(const QChar &newNonBreakingSpace);

    /*!
     * \brief Returns the superscript entries
     * \return A hash of superscript replacements
     */
    [[nodiscard]] QHash<QString, QString> superScriptEntries() const;
    /*!
     * \brief Sets the superscript entries
     * \param newSuperScriptEntries A hash of superscript replacements
     */
    void setSuperScriptEntries(const QHash<QString, QString> &newSuperScriptEntries);

    /*!
     * \brief Writes the autocorrection data to file
     * \param filename The path to write to (uses default if empty)
     */
    void writeAutoCorrectionFile(const QString &filename = QString());
    /*!
     * \brief Returns the maximum length of strings to find for replacement
     * \return The maximum find string length
     */
    [[nodiscard]] int maxFindStringLength() const;

    /*!
     * \brief Returns the minimum length of strings to find for replacement
     * \return The minimum find string length
     */
    [[nodiscard]] int minFindStringLength() const;

    /*!
     * \brief Loads autocorrection from a local file
     * \param localFileName The local file name to load from
     * \param fname The full path to the file
     */
    void loadLocalFileName(const QString &localFileName, const QString &fname);
    /*!
     * \brief Loads autocorrection from a global file
     * \param fname The path to the global autocorrection file
     */
    void loadGlobalFileName(const QString &fname);

    /*!
     * \brief Returns the double French quote characters
     * \return The double French quotes
     */
    [[nodiscard]] AutoCorrectionUtils::TypographicQuotes doubleFrenchQuotes() const;
    /*!
     * \brief Sets the double French quote characters
     * \param newDoubleFrenchQuotes The double French quotes to use
     */
    void setDoubleFrenchQuotes(const AutoCorrectionUtils::TypographicQuotes &newDoubleFrenchQuotes);

    /*!
     * \brief Returns the custom writable path for autocorrection files
     * \return The custom writable path
     */
    [[nodiscard]] QString customWritablePath() const;
    /*!
     * \brief Sets the custom writable path for autocorrection files
     * \param path The custom writable path
     */
    void setCustomWritablePath(const QString &path);

    /*!
     * \brief Returns the custom system path for autocorrection files
     * \return The custom system path
     */
    [[nodiscard]] QString customSystemPath() const;
    /*!
     * \brief Sets the custom system path for autocorrection files
     * \param path The custom system path
     */
    void setCustomSystemPath(const QString &path);

private:
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void readAutoCorrectionFile(bool forceGlobal = false);
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT QString containsAutoCorrectionFile(const QString &fileName);

    friend class AutoCorrectionSettingsPrivate;
    std::unique_ptr<AutoCorrectionSettingsPrivate> const d;
};
}
/*!
 * \brief Outputs the AutoCorrectionSettings to a debug stream
 * \param d The debug stream
 * \param t The AutoCorrectionSettings to output
 * \return The debug stream
 */
TEXTAUTOCORRECTIONCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoCorrectionCore::AutoCorrectionSettings &t);
