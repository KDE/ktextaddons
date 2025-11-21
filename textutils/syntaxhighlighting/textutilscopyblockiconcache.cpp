/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
    mCopyBlockUrl.clear();
    mTemporaryFile.release();
}

QString TextUtilsCopyBlockIconCache::copyBlockUrl()
{
    if (mCopyBlockUrl.isEmpty()) {
        saveIconToTempFile(u"edit-copy"_s);
    }
    // qDebug() << " mCopyBlockUrl" << mCopyBlockUrl;
    return mCopyBlockUrl;
}

void TextUtilsCopyBlockIconCache::saveIconToTempFile(const QString &iconName)
{
    const QIcon icon = QIcon::fromTheme(iconName);
    if (icon.isNull()) {
        qCWarning(TEXTUTILS_LOG) << "Icon is not found:" << iconName;
        return;
    }

    const int iconSize = KIconLoader::global()->currentSize(KIconLoader::Small);
    const QPixmap pixmap = icon.pixmap(iconSize, iconSize);

    mTemporaryFile.reset(new QTemporaryFile(QDir::tempPath() + u"/icon_XXXXXX.png"_s));
    if (!mTemporaryFile->open()) {
        qCWarning(TEXTUTILS_LOG) << "Impossible to create temporary file.";
        mTemporaryFile.reset();
        return;
    }

    if (!pixmap.save(mTemporaryFile.get(), "PNG")) {
        qCWarning(TEXTUTILS_LOG) << "Impossible to save file.";
        return;
    }
    mCopyBlockUrl = mTemporaryFile->fileName();
}
