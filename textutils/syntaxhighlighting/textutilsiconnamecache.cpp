/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textutilsiconnamecache.h"
#include "textutils_debug.h"
#include <KIconLoader>
using namespace TextUtils;
using namespace Qt::Literals::StringLiterals;
TextUtilsIconNameCache *TextUtilsIconNameCache::self()
{
    static TextUtilsIconNameCache s_self;
    return &s_self;
}

bool TextUtilsIconNameCache::Entry::operator<(const Entry &other) const
{
    if (const int fileNameCompare = fileName.compare(other.fileName); fileNameCompare != 0) {
        return fileNameCompare < 0;
    } else {
        return size < other.size;
    }
}

void TextUtilsIconNameCache::clearCache()
{
    mCachedEntries.clear();
}

QString TextUtilsIconNameCache::iconPath(const QString &name, int size) const
{
    const Entry entry{name, size};

    // We store the file name even when it's empty, so that we don't call
    // KIconLoader::global() again and again for an icon which can't be found.
    if (const auto it = mCachedEntries.constFind(entry); it != mCachedEntries.constEnd()) {
        return it.value();
    }

    QString fileName = KIconLoader::global()->iconPath(name, size, true);
    if (fileName.isEmpty()) {
        qCWarning(TEXTUTILS_LOG) << "Icon name:" << name << "not found";
    } else if (fileName.startsWith(":/"_L1)) {
        fileName = u"qrc"_s + fileName;
    }
    mCachedEntries.insert(entry, fileName);
    return fileName;
}
