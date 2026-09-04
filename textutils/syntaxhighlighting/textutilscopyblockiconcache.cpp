/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textutilscopyblockiconcache.h"
#include "textutils_syntaxhighlighting_debug.h"

#include <QDir>
#include <QIcon>
#include <QTemporaryFile>
#include <kiconloader.h>

using namespace TextUtils;
using namespace Qt::Literals::StringLiterals;

TextUtilsCopyBlockIconCache *TextUtilsCopyBlockIconCache::self()
{
    static TextUtilsCopyBlockIconCache s_self;
    return &s_self;
}

void TextUtilsCopyBlockIconCache::clear()
{
    mIconUrlMap.clear();
    mIconTemporaryFileMap.clear();
}

QString TextUtilsCopyBlockIconCache::iconUrl(TextUtilsCopyBlockIconCache::IconType type)
{
    const QString url = mIconUrlMap.value(type);
    if (url.isEmpty()) {
        return saveIconToTempFile(type);
    }
    return url;
}

QString TextUtilsCopyBlockIconCache::iconName(TextUtilsCopyBlockIconCache::IconType type) const
{
    switch (type) {
    case TextUtilsCopyBlockIconCache::IconType::Unknown:
        return {};
    case TextUtilsCopyBlockIconCache::IconType::CopyText:
        return u"edit-copy"_s;
    case TextUtilsCopyBlockIconCache::IconType::InsertText:
        return u"insert-text"_s;
    }
    qCWarning(TEXTUTILS_SYNTAXHIGHLIGHTING_LOG) << "Icon name not defined";
    return {};
}

QString TextUtilsCopyBlockIconCache::saveIconToTempFile(TextUtilsCopyBlockIconCache::IconType type)
{
    const QIcon icon = QIcon::fromTheme(iconName(type));
    if (icon.isNull()) {
        qCWarning(TEXTUTILS_SYNTAXHIGHLIGHTING_LOG) << "Icon is not found:" << static_cast<int>(type);
        return {};
    }

    const int iconSize = KIconLoader::global()->currentSize(KIconLoader::Small);
    const QPixmap pixmap = icon.pixmap(iconSize, iconSize);

    auto temp = std::make_unique<QTemporaryFile>(QDir::tempPath() + u"/icon_XXXXXX.png"_s);
    if (!temp->open()) {
        qCWarning(TEXTUTILS_SYNTAXHIGHLIGHTING_LOG) << "Impossible to create temporary file.";
        return {};
    }

    if (!pixmap.save(temp.get(), "PNG")) {
        qCWarning(TEXTUTILS_SYNTAXHIGHLIGHTING_LOG) << "Impossible to save file.";
        return {};
    }

    // The file is kept open so that it's not removed, but QFile buffers writes.
    // Without flushing, the icon is still in the write buffer and the file on disk is empty.
    if (!temp->flush()) {
        qCWarning(TEXTUTILS_SYNTAXHIGHLIGHTING_LOG) << "Impossible to flush file.";
        return {};
    }
    const QString fileName = temp->fileName();
    mIconUrlMap.insert(type, fileName);
    mIconTemporaryFileMap.insert_or_assign(type, std::move(temp));
    return fileName;
}
