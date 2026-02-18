/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QMap>
#include <QString>
namespace TextUtils
{
/*!
 * \brief The TextUtilsBlockCodeManager class
 * \author Laurent Montel <montel@kde.org>
 * \class TextUtils::TextUtilsBlockCodeManager
 * \inheaderfile TextUtils/TextUtilsBlockCodeManager
 * \inmodule TextUtils
 */
class TEXTUTILS_EXPORT TextUtilsBlockCodeManager
{
public:
    /*!
     * \brief Returns the singleton instance of TextUtilsBlockCodeManager
     * \return Pointer to the singleton instance
     */
    static TextUtilsBlockCodeManager *self();
    /*!
     * \brief Inserts or updates a block code entry
     * \param identifier The unique identifier for the block code
     * \param blockCode The block code content to store
     */
    void insert(const QString &identifier, const QString &blockCode);
    /*!
     * \brief Retrieves a block code by identifier
     * \param identifier The identifier of the block code to retrieve
     * \return The block code content, or empty string if not found
     */
    [[nodiscard]] QString blockCode(const QString &identifier) const;

    /*!
     * \brief Clears all cached block codes
     */
    void clear();

private:
    QMap<QString, QString> mCacheBlockCode;
};
}
