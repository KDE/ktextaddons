/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "autocorrectionsettings.h"
#include "textautocorrectioncore_export.h"
#include <QTextCursor>

namespace TextAutoCorrectionCore
{
class AutoCorrectionPrivate;
/*!\n
 * \class TextAutoCorrectionCore::AutoCorrection
 * \inmodule TextAutoCorrectionCore
 * \inheaderfile TextAutoCorrectionCore/AutoCorrection
 *
 * \brief The AutoCorrection class
 *
 * Provides automatic text correction functionality including quote replacement,
 * capitalization, and other typographic corrections.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONCORE_EXPORT AutoCorrection
{
public:
    /*!
     * \brief Constructs an AutoCorrection instance
     */
    AutoCorrection();
    /*!
     * \brief Destroys the AutoCorrection instance
     */
    ~AutoCorrection();

    /*!
     * \brief Writes the configuration to settings
     */
    void writeConfig();
    /*!
     * \brief Reads the configuration from settings
     */
    void readConfig();

    /*!
     * \brief Applies autocorrection to the document at the given position
     * \param htmlMode true if the document contains HTML content
     * \param document The text document to correct
     * \param position The cursor position (will be updated)
     * \return true if corrections were applied
     */
    bool autocorrect(bool htmlMode, QTextDocument &document, int &position);

    /*!
     * \brief Loads the global autocorrection file
     * \param fname The path to the autocorrection file
     */
    void loadGlobalFileName(const QString &fname);

    /*!
     * \brief Returns the autocorrection settings
     * \return A pointer to the AutoCorrectionSettings instance
     */
    [[nodiscard]] AutoCorrectionSettings *autoCorrectionSettings() const;
    /*!
     * \brief Sets the autocorrection settings
     * \param newAutoCorrectionSettings The new AutoCorrectionSettings instance
     */
    void setAutoCorrectionSettings(AutoCorrectionSettings *newAutoCorrectionSettings);

    /*!
     * \brief Writes the autocorrection data to an XML file
     * \param filename The path to write the XML file to
     */
    void writeAutoCorrectionXmlFile(const QString &filename);

private:
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void fixTwoUppercaseChars();
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT bool singleSpaces() const;
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void capitalizeWeekDays();
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT bool autoFractions() const;
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void uppercaseFirstCharOfSentence();
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT int advancedAutocorrect();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void replaceTypographicQuotes();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void superscriptAppendix();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void addNonBreakingSpace();

    TEXTAUTOCORRECTIONCORE_NO_EXPORT void selectPreviousWord(QTextCursor &cursor, int cursorPosition);
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void selectStringOnMaximumSearchString(QTextCursor &cursor, int cursorPosition);

    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT bool autoFormatURLs();
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT bool autoBoldUnderline();

    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT QString autoDetectURL(const QString &_word) const;
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT bool excludeToUppercase(const QString &word) const;
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT QColor linkColor();
    friend class AutoCorrectionPrivate;
    std::unique_ptr<AutoCorrectionPrivate> const d;
};
}
