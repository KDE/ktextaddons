/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textutilsiconnamecache.h"
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
    const int fileNameCompare = fileName.compare(other.fileName);
    if (fileNameCompare != 0) {
        return fileNameCompare < 0;
    } else {
        return size < other.size;
    }
}

QString TextUtilsIconNameCache::iconPath(const QString &name, int size) const
{
    Entry entry;
    entry.fileName = name;
    entry.size = size;

    const QString val = mCachedEntries.value(entry);
    if (!val.isEmpty()) {
        return val;
    }

    QString fileName = KIconLoader::global()->iconPath(name, size);
    if (fileName.startsWith(QLatin1StringView(":/"))) {
        fileName = u"qrc"_s + fileName;
    }
    mCachedEntries.insert(entry, fileName);
    return fileName;
}
