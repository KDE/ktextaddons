/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QString>
#include <map>
#include <memory>
class QTemporaryFile;
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
        InsertText,
    };

    /*!
     * \brief Returns the singleton instance of TextUtilsCopyBlockIconCache
     * \return Pointer to the singleton instance
     */
    static TextUtilsCopyBlockIconCache *self();

    // The class is dllexported: without deleting them explicitly, MSVC instantiates
    // the implicit copy members which can't copy the std::unique_ptr map.
    TextUtilsCopyBlockIconCache(const TextUtilsCopyBlockIconCache &) = delete;
    TextUtilsCopyBlockIconCache &operator=(const TextUtilsCopyBlockIconCache &) = delete;
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
    TextUtilsCopyBlockIconCache() = default;
    ~TextUtilsCopyBlockIconCache();

    [[nodiscard]] TEXTUTILS_NO_EXPORT QString saveIconToTempFile(TextUtilsCopyBlockIconCache::IconType type);
    [[nodiscard]] static TEXTUTILS_NO_EXPORT QString iconName(TextUtilsCopyBlockIconCache::IconType type);
    struct Entry {
        QString name;
        std::unique_ptr<QTemporaryFile> temporaryFile;
    };
    std::map<IconType, Entry> mIconMap;
};
}
