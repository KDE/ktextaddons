/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>
#include <QMetaType>
#include <QSet>
#include <QString>

#include "autocorrectionutils.h"

#include "textautocorrectioncore_export.h"
namespace TextAutoCorrectionCore
{
/*!
 * \class TextAutoCorrectionCore::ImportAbstractAutocorrection
 * \inmodule TextAutoCorrectionCore
 * \inheaderfile TextAutoCorrectionCore/ImportAbstractAutocorrection
 *
 * \brief Abstract base class for importing autocorrection data from various formats.
 *
 * This class provides an interface for importing autocorrection rules, exceptions,
 * and typographic quote settings from different file formats.
 */
class TEXTAUTOCORRECTIONCORE_EXPORT ImportAbstractAutocorrection
{
    Q_GADGET
public:
    /*!
     * \enum LoadAttribute
     * Specifies what data to load during import.
     */
    enum LoadAttribute {
        All = 0, /*!< Load all autocorrection data */
        SuperScript, /*!< Load only superscript entries */
    };
    Q_ENUM(LoadAttribute)

    /*!
     * \brief Constructs an ImportAbstractAutocorrection instance
     */
    ImportAbstractAutocorrection();
    /*!
     * \brief Destroys the ImportAbstractAutocorrection instance
     */
    virtual ~ImportAbstractAutocorrection();

    /*!
     * \brief Imports autocorrection data from a file
     * \param fileName The path to the file to import from
     * \param errorMessage Will be set to an error message if import fails
     * \param loadAttribute Specifies what data to load
     * \return true if import was successful, false otherwise
     */
    virtual bool import(const QString &fileName, QString &errorMessage, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) = 0;

    /*!
     * \brief Returns the list of uppercase exceptions
     * \return The set of words that should not have their first character uppercased
     */
    [[nodiscard]] QSet<QString> upperCaseExceptions() const;
    /*!
     * \brief Returns the list of two-upper-letter exceptions
     * \return The set of words that should not be changed from two uppercase letters
     */
    [[nodiscard]] QSet<QString> twoUpperLetterExceptions() const;
    /*!
     * \brief Returns the autocorrection entries
     * \return A hash of autocorrection replacements
     */
    [[nodiscard]] QHash<QString, QString> autocorrectEntries() const;
    /*!
     * \brief Returns the superscript entries
     * \return A hash of superscript replacements
     */
    [[nodiscard]] QHash<QString, QString> superScriptEntries() const;

    /*!
     * \brief Returns the typographic single quote characters
     * \return The typographic single quotes
     */
    [[nodiscard]] AutoCorrectionUtils::TypographicQuotes typographicSingleQuotes() const;
    /*!
     * \brief Returns the typographic double quote characters
     * \return The typographic double quotes
     */
    [[nodiscard]] AutoCorrectionUtils::TypographicQuotes typographicDoubleQuotes() const;

    /*!
     * \brief Returns the maximum length of strings to find for replacement
     * \return The maximum find string length
     */
    [[nodiscard]] int maxFindStringLenght() const;

    /*!
     * \brief Returns the minimum length of strings to find for replacement
     * \return The minimum find string length
     */
    [[nodiscard]] int minFindStringLenght() const;

protected:
    int mMaxFindStringLength = 0;
    int mMinFindStringLength = 0;
    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;
    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;
    AutoCorrectionUtils::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrectionUtils::TypographicQuotes mTypographicDoubleQuotes;
};
}
