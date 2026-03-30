/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QMap>
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
    enum class IconType : uint8_t {
        Unknown = 0,
        CopyText,
        InsertText
    };

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
     * \brief iconUrl
     * \param type
     * \return
     */
    [[nodiscard]] QString iconUrl(TextUtilsCopyBlockIconCache::IconType type);

private:
    TEXTUTILS_NO_EXPORT [[nodiscard]] QString saveIconToTempFile(TextUtilsCopyBlockIconCache::IconType type);
    TEXTUTILS_NO_EXPORT [[nodiscard]] QString iconName(TextUtilsCopyBlockIconCache::IconType type) const;
    QMap<IconType, QString> mIconUrlMap;
    QMap<IconType, QTemporaryFile *> mIconTemporaryFileMap;
};
}
