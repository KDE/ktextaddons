/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratetexticonnamecache.h"
#include <KIconLoader>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextIconNameCache *TextAutoGenerateTextIconNameCache::self()
{
    static TextAutoGenerateTextIconNameCache s_self;
    return &s_self;
}

bool TextAutoGenerateTextIconNameCache::Entry::operator<(const Entry &other) const
{
    const int fileNameCompare = fileName.compare(other.fileName);
    if (fileNameCompare != 0) {
        return fileNameCompare < 0;
    } else {
        return size < other.size;
    }
}

QString TextAutoGenerateTextIconNameCache::iconPath(const QString &name, int size) const
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
