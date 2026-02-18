/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "importabstractautocorrection.h"
#include "textautocorrectioncore_export.h"
namespace TextAutoCorrectionCore
{
/*!
 * \class TextAutoCorrectionCore::ImportKMailAutocorrection
 * \inmodule TextAutoCorrectionCore
 * \inheaderfile TextAutoCorrectionCore/ImportKMailAutocorrection
 *
 * \brief Imports autocorrection data from KMail format.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONCORE_EXPORT ImportKMailAutocorrection : public ImportAbstractAutocorrection
{
public:
    /*!
     * \brief Constructs an ImportKMailAutocorrection instance
     */
    ImportKMailAutocorrection();
    /*!
     * \brief Destroys the ImportKMailAutocorrection instance
     */
    ~ImportKMailAutocorrection() override;
    /*!
     * \brief Imports autocorrection data from a KMail file
     * \param fileName The path to the KMail autocorrection file
     * \param errorMessage Will be set to an error message if import fails
     * \param loadAttribute Specifies what data to load
     * \return true if import was successful, false otherwise
     */
    [[nodiscard]] bool import(const QString &fileName, QString &errorMessage, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) override;
};
}
