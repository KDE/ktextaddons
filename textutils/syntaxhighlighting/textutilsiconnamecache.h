/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
   code based on messageviewer/src/utils/iconnamecache.h
*/
#pragma once
#include "textutils_export.h"
#include <QMap>
#include <QString>

namespace TextUtils
{
/*!
 * \brief The TextUtilsIconNameCache class
 * \author Laurent Montel <montel@kde.org>
 * \class TextUtils::TextUtilsIconNameCache
 * \inheaderfile TextUtils/TextUtilsIconNameCache
 * \inmodule TextUtils
 */
class TEXTUTILS_EXPORT TextUtilsIconNameCache
{
public:
    /*!
     * \brief Returns the singleton instance of TextUtilsIconNameCache
     * \return Pointer to the singleton instance
     */
    static TextUtilsIconNameCache *self();
    /*!
     * \brief Gets the icon path for an icon by name and size
     * \param name The name of the icon
     * \param size The desired size of the icon
     * \return The path to the icon file
     */
    [[nodiscard]] QString iconPath(const QString &name, int size) const;
    /*!
     * \brief Clears the icon cache
     */
    void clearCache();

private:
    class Entry
    {
    public:
        QString fileName;
        int size;
        [[nodiscard]] bool operator<(const Entry &other) const;
    };

    mutable QMap<Entry, QString> mCachedEntries;
    mutable QString mPicsPath;
};
}
