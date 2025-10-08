/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
   code based on messageviewer/src/utils/iconnamecache.h
*/
#pragma once

#include <QMap>
#include <QString>

namespace TextAutoGenerateText
{
class TextAutoGenerateTextIconNameCache
{
public:
    static TextAutoGenerateTextIconNameCache *self();
    [[nodiscard]] QString iconPath(const QString &name, int size) const;

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
