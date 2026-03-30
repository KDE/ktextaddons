/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textutilscopyblockiconcache.h"
#include "textutils_debug.h"

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
    qDeleteAll(mIconTemporaryFileMap);
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
        return u"edit-copy"_s;
    }
    qCWarning(TEXTUTILS_LOG) << "Icon name not defined";
    return {};
}

QString TextUtilsCopyBlockIconCache::saveIconToTempFile(TextUtilsCopyBlockIconCache::IconType type)
{
    const QIcon icon = QIcon::fromTheme(iconName(type));
    if (icon.isNull()) {
        qCWarning(TEXTUTILS_LOG) << "Icon is not found:" << static_cast<int>(type);
        return {};
    }

    const int iconSize = KIconLoader::global()->currentSize(KIconLoader::Small);
    const QPixmap pixmap = icon.pixmap(iconSize, iconSize);

    auto temp = new QTemporaryFile(QDir::tempPath() + u"/icon_XXXXXX.png"_s);
    if (!temp->open()) {
        qCWarning(TEXTUTILS_LOG) << "Impossible to create temporary file.";
        temp = nullptr;
        return {};
    }

    if (!pixmap.save(temp, "PNG")) {
        qCWarning(TEXTUTILS_LOG) << "Impossible to save file.";
        return {};
    }
    mIconUrlMap.insert(type, temp->fileName());
    mIconTemporaryFileMap.insert(type, temp);
    return temp->fileName();
}
