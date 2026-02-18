/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "importabstractautocorrection.h"
#include "textautocorrectioncore_export.h"
class QTemporaryDir;
class KZip;
class QDomDocument;
class QFile;
class KArchiveDirectory;

namespace TextAutoCorrectionCore
{
/*!
 * \class TextAutoCorrectionCore::ImportLibreOfficeAutocorrection
 * \inmodule TextAutoCorrectionCore
 * \inheaderfile TextAutoCorrectionCore/ImportLibreOfficeAutocorrection
 *
 * \brief Imports autocorrection data from LibreOffice format.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONCORE_EXPORT ImportLibreOfficeAutocorrection : public ImportAbstractAutocorrection
{
public:
    /*!
     * \brief Constructs an ImportLibreOfficeAutocorrection instance
     */
    ImportLibreOfficeAutocorrection();
    /*!
     * \brief Destroys the ImportLibreOfficeAutocorrection instance
     */
    ~ImportLibreOfficeAutocorrection() override;

    /*!
     * \brief Imports autocorrection data from a LibreOffice file
     * \param fileName The path to the LibreOffice autocorrection file
     * \param errorMessage Will be set to an error message if import fails
     * \param loadAttribute Specifies what data to load
     * \return true if import was successful, false otherwise
     */
    [[nodiscard]] bool import(const QString &fileName, QString &errorMessage, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) override;

private:
    enum class Type : int8_t {
        DOCUMENT,
        SENTENCE,
        WORD,
    };
    Q_ENUM(Type)

    TEXTAUTOCORRECTIONCORE_NO_EXPORT void importAutoCorrectionFile();
    TEXTAUTOCORRECTIONCORE_NO_EXPORT void closeArchive();
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT bool loadDomElement(QDomDocument &doc, QFile *file);
    [[nodiscard]] TEXTAUTOCORRECTIONCORE_NO_EXPORT bool importFile(Type type, const KArchiveDirectory *archiveDirectory);
    KZip *mArchive = nullptr;
    QTemporaryDir *mTempDir = nullptr;
};
}
