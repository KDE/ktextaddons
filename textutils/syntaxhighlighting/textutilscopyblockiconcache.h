/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QString>
#include <QTemporaryFile>
#include <memory>

namespace TextUtils
{
/*!
 * \brief The TextUtilsCopyBlockIconCache class
 * \author Laurent Montel <montel@kde.org>
 * \class TextUtils::TextUtilsCopyBlockIconCache
 * \inheaderfile TextUtils/TextUtilsCopyBlockIconCache
 * \inmodule TextUtils
 */
class TEXTUTILS_EXPORT TextUtilsCopyBlockIconCache
{
public:
    /*!
     * \brief Returns the singleton instance of TextUtilsCopyBlockIconCache
     * \return Pointer to the singleton instance
     */
    static TextUtilsCopyBlockIconCache *self();
    /*!
     * \brief Clears the cached icon
     */
    void clear();

    /*!
     * \brief Returns the URL of the copy block icon
     * \return The URL string for the copy icon
     */
    [[nodiscard]] QString copyBlockUrl();

private:
    TEXTUTILS_NO_EXPORT void saveIconToTempFile(const QString &iconName);
    QString mCopyBlockUrl;
    std::unique_ptr<QTemporaryFile> mTemporaryFile;
};
}
